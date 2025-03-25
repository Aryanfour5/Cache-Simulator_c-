🛠️ Cache Replacement Policy Simulation with Multi-threading
This project simulates Cache Replacement Policies (LRU and LFU) with multi-threading for efficient memory access handling. It demonstrates how cache management works in real-world systems, handling concurrent memory accesses using C++ threads.

🚀 Features
✅ LRU (Least Recently Used) and LFU (Least Frequently Used) cache policies.
✅ Multi-threaded simulation for concurrent memory access.
✅ Efficient cache handling with locality principles.
✅ Cache display and interactive menu.
✅ Thread-safe cache operations using std::mutex.

⚙️ Technologies Used
Language: C++

Libraries: iostream, vector, queue, unordered_map, thread, mutex, algorithm

📚 How to Compile and Run
1. Compilation
Use the following command to compile the program:

bash
Copy
Edit
g++ -std=c++17 -o cache_simulation cache_simulation.cpp -lpthread
2. Run the Program
bash
Copy
Edit
./cache_simulation
🛠️ Usage
Select Cache Replacement Policy

1 → LRU Cache

2 → LFU Cache

Access Memory

Choose memory addresses concurrently with multiple threads.

Display Cache

View the current cache state.

Change Cache Policy

Switch between LRU and LFU policies during execution.

Exit

Quit the simulation.

⚙️ Sample Execution
bash
Copy
Edit
Cache size: 16  
Options:  
1. Access Memory Address  
2. Display Cache  
3. Change Cache Replacement Policy  
4. Exit  
Enter your choice: 1  
Enter a memory address to access (0-31): 10  
Enter the number of threads: 4  
Simulating with 4 threads...  
Thread 0: Accessed Address 10  
Thread 1: Accessed Address 11  
Thread 2: Accessed Address 12  
Thread 3: Accessed Address 13  

LRU Cache miss - Address 10 added to the cache.  
LRU Cache miss - Address 11 added to the cache.  
LRU Cache miss - Address 12 added to the cache.  
LRU Cache miss - Address 13 added to the cache.  
🔥 Performance Considerations
Multi-threading enhances simulation realism, mimicking concurrent memory access scenarios.

std::mutex ensures thread-safe cache access.

Improved cache locality handling by prefetching nearby addresses.

📌 Future Enhancements
✅ Support for FIFO (First-In-First-Out) policy.

✅ Advanced cache metrics (hit/miss ratio, access time).

✅ Customizable cache and memory sizes.

🤝 Contributing
Feel free to fork the repository and submit pull requests to add new cache policies or optimizations.

📄 License
This project is licensed under the MIT License.

🔥 Author
💡 Aryan Bachute  
👨‍💻 Contact:bachutearyan@gmail.com
