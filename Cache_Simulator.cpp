#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <thread>
#include <mutex>
#include <random>
#include <chrono>

using namespace std;

const int CACHE_SIZE = 16;
const int MEMORY_SIZE = 32;
const int NUM_THREADS = 4;
const int NUM_ACCESSES = 10;

mutex cacheMutex;

class Cache {
protected:
    vector<int> cache;
    vector<int> memory;

public:
    Cache(int size) {
        cache.resize(size, -1);
        for (int i = 0; i < MEMORY_SIZE; i++) {
            memory.push_back(i);
        }
    }

    virtual ~Cache() {}

    virtual void accessMemory(int address) = 0;

    void displayCache() {
        lock_guard<mutex> lock(cacheMutex);  // Lock for thread safety
        cout << "Current Cache: ";
        for (int i = 0; i < CACHE_SIZE; i++) {
            if (cache[i] == -1) {
                cout << "empty ";
            } else {
                cout << cache[i] << " ";
            }
        }
        cout << endl;
    }
};

class LRUCache : public Cache {
private:
    vector<int> cacheOrder;

public:
    LRUCache(int size) : Cache(size) {}

    void accessMemory(int address) override {
        lock_guard<mutex> lock(cacheMutex);  // Lock for thread safety

        auto it = find(cache.begin(), cache.end(), address);
        if (it != cache.end()) {
            cout << "LRU Cache hit!" << endl;
            cacheOrder.erase(remove(cacheOrder.begin(), cacheOrder.end(), address), cacheOrder.end());
            cacheOrder.push_back(address);
        } else {
            if (cacheOrder.size() == CACHE_SIZE) {
                int removedAddress = cacheOrder.front();
                cacheOrder.erase(cacheOrder.begin());
                auto index = find(cache.begin(), cache.end(), removedAddress);
                *index = address;
                cacheOrder.push_back(address);
            } else {
                cacheOrder.push_back(address);
                auto emptySlot = find(cache.begin(), cache.end(), -1);
                *emptySlot = address;
            }
            cout << "LRU Cache miss - Address " << address << " added to the cache." << endl;
        }
    }
};

class LFUCache : public Cache {
private:
    unordered_map<int, int> frequency;

public:
    LFUCache(int size) : Cache(size) {}

    void accessMemory(int address) override {
        lock_guard<mutex> lock(cacheMutex);  // Lock for thread safety

        auto it = find(cache.begin(), cache.end(), address);
        if (it != cache.end()) {
            cout << "LFU Cache hit!" << endl;
            frequency[address]++;
        } else {
            if (cache.size() == CACHE_SIZE) {
                int minFreqAddress = cache.front();
                for (int val : cache) {
                    if (frequency[val] < frequency[minFreqAddress]) {
                        minFreqAddress = val;
                    }
                }
                auto index = find(cache.begin(), cache.end(), minFreqAddress);
                *index = address;
                frequency[address] = 1;
            } else {
                cache.push_back(address);
                frequency[address] = 1;
            }
            cout << "LFU Cache miss - Address " << address << " added to the cache." << endl;
        }
    }
};

// Simulate concurrent cache access by multiple threads
void simulateCacheAccess(Cache* cache, int threadID) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, MEMORY_SIZE - 1);

    for (int i = 0; i < NUM_ACCESSES; ++i) {
        int address = dist(gen);
        cout << "Thread " << threadID << " accessing address: " << address << endl;
        cache->accessMemory(address);
        this_thread::sleep_for(chrono::milliseconds(100));  // Simulate delay
    }
}

int main() {
    Cache* cachePolicy = nullptr;

    cout << "Cache size: " << CACHE_SIZE << endl;

    while (true) {
        cout << "\nOptions:\n1. Access Memory (Multi-threaded)\n2. Display Cache\n3. Change Cache Replacement Policy\n4. Exit\n";
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            if (!cachePolicy) {
                cout << "Cache is not initialized. Please select a replacement policy first.\n";
                continue;
            }

            vector<thread> threads;

            // Launch multiple threads for concurrent access
            for (int i = 0; i < NUM_THREADS; ++i) {
                threads.emplace_back(simulateCacheAccess, cachePolicy, i + 1);
            }

            // Join all threads
            for (auto& t : threads) {
                t.join();
            }
        } 
        else if (choice == 2) {
            if (cachePolicy) {
                cachePolicy->displayCache();
            } else {
                cout << "Cache is not initialized. Please select a replacement policy." << endl;
            }
        } 
        else if (choice == 3) {
            if (cachePolicy) {
                delete cachePolicy;
            }

            int replacementChoice;
            cout << "Select Cache Replacement Policy:\n1. LRU\n2. LFU\nEnter your choice: ";
            cin >> replacementChoice;

            if (replacementChoice == 1) {
                cachePolicy = new LRUCache(CACHE_SIZE);
                cout << "LRU Cache selected." << endl;
            } 
            else if (replacementChoice == 2) {
                cachePolicy = new LFUCache(CACHE_SIZE);
                cout << "LFU Cache selected." << endl;
            } 
            else {
                cout << "Invalid policy choice. Using default LRU Cache." << endl;
                cachePolicy = new LRUCache(CACHE_SIZE);
            }
        } 
        else if (choice == 4) {
            if (cachePolicy) {
                delete cachePolicy;
            }
            break;
        } 
        else {
            cout << "Invalid choice. Try again." << endl;
        }
    }

    return 0;
}
