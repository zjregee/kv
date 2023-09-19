#pragma once

#include "common/page.h"
#include <fcntl.h>
#include <iostream>
#include <unistd.h>
#include <list>
#include <unordered_map>
#include <string>
#include <mutex>

namespace KV {

class DiskAdaptor {
public:
    void Init(const string &disk_name, size_t memory_capcaity = 16384) {
        capacity_ = memory_capcaity;
        fd_ = open(disk_name.c_str(), O_RDWR);
        if (fd_ == -1) {
            perror("open disk error");
            exit(1);
        }
    }

    Page* ReadPage(uint32_t page_id) {
        Page* page = Get(page_id);
        if (page != nullptr) {
            return page;
        }
        page = new Page();
        off_t offset = page_id * PAGE_SIZE;
        lseek(fd_, offset, SEEK_SET);
        read(fd_, page->GetData(), PAGE_SIZE);
        Put(page_id, page);
        return page;
    }

    void WritePage(uint32_t page_id, Page* p) {
        Put(page_id, p);
    }

    ~DiskAdaptor() {
        if (fd != -1) {
            close(fd_);
        }
        for (const auto &entry : cache_list_) {
            delete entry.second;
        }
        cache_list_.clear();
        cache_map_.clear();
    }

private:
    int fd_;
    size_t capacity_;
    std::list<std::pair<uint32_t, Page*>> cache_list_;
    std::unordered_map<int, std::list<std::pair<uint32_t, Page*>>::iterator> cache_map_;
    std::mutex mutex_;

    Page* Get(uint32_t page_id) {
        auto iter = cache_map_.find(page_id);
        if (iter == cache_map_.end()) {
            return nullptr;
        }
        cache_list_.splice(cache_list_.begin(), cache_list_, iter->second);
        return iter->second->second;
    }

    void Put(uint32_t page_id, Page* p) {
        auto iter = cache_map_.find(page_id);
        if (iter != cache_map_.end()) {
            iter->second->second = p;
            cache_list_.splice(cache_list_.begin(), cache_list_, iter->second);
            return;
        }
        if (cache_map_.size() == capacity_) {
            uint32_t last_page_id = cache_list_.back().first;
            Page* last_page = cache_list_.back().second;
            off_t offset = last_page_id * PAGE_SIZE;
            lseek(fd_, offset, SEEK_SET);
            write(fd_, last_page->GetData(), PAGE_SIZE);
            cache_list_.pop_back();
            cache_map_.erase(last_page_id);
            delete last_page;
        }
        cache_list_.emplace_front(page_id, p);
        cache_map_[page_id] = cache_list_.begin();
    }
};

}
