#include <cstddef>
#include <functional>
#include <algorithm>
#include <iostream>

using namespace std; 

template<typename K, typename V>
class hash_table {
    private: 
        struct node {
            K key; 
            V value; 
            node* next; 
            node(const K& k, const V& v) : key(k), value(v), next(nullptr) {} 
        };

        node** table; 
        size_t capacity; 
        size_t num_elements; 
    
        size_t hashFunction(const K& k) const {
            hash<K> hasher; 
            return hasher(k) % capacity; 
        }

    public: 

        hash_table(size_t cap = 2000003) : capacity(cap), num_elements(0) {
            table = new node* [capacity]; 
            for (size_t i = 0; i < capacity; i++) {
                table[i] = nullptr; 
            }
        }

        ~hash_table() {
            for (size_t i = 0; i < capacity; i++) {
                node* current = table[i]; 
                while (current != nullptr) {
                    node* temp = current; 
                    current = current->next; 
                    delete temp; 
                }
            }
            delete[] table; 
        }


        hash_table(const hash_table& other) : capacity(other.capacity), num_elements(other.num_elements) {
            table = new node*[capacity];
            
            for (size_t i = 0; i < capacity; i++) {
                table[i] = nullptr;
                node* current = other.table[i];
                node* tail = nullptr; 
                
                while (current != nullptr) {
                    node* newNode = new node(current->key, current->value);
                    if (table[i] == nullptr) {
                        table[i] = newNode;
                    } else {
                        tail->next = newNode;
                    }
                    tail = newNode;
                    current = current->next;
                }
            }
        }

        hash_table& operator=(const hash_table& other) {
            if (this != &other) { 
                hash_table temp(other); 
                
                std::swap(capacity, temp.capacity);
                std::swap(num_elements, temp.num_elements);
                std::swap(table, temp.table);
                
            }
            return *this;
        }

        void insert(const K& k, const V& v) {
            size_t index = hashFunction(k);
            node* current = table[index]; 

            while (current != nullptr) {
                if (current->key == k) {
                    current->value = v; 
                    return; 
                }
                current = current->next; 
            }
            
            node* newNode = new node(k, v); 
            newNode->next = table[index]; 
            table[index] = newNode; 
            num_elements++; 
        }

        bool search(const K& k, V& out_value) const {
            size_t index = hashFunction(k); 
            node* current = table[index]; 

            while (current != nullptr) {
                if (current->key == k) {
                    out_value = current->value; 
                    return true; 
                }
                current = current->next; 
            }
            return false; 
        }

        bool remove(const K& k) {
            size_t index = hashFunction(k); 
            node* current = table[index]; 
            node* prev = nullptr; 

            while (current != nullptr) { 
                if (current->key == k) {
                    if (prev == nullptr) {
                        table[index] = current->next; 
                    } else {
                        prev->next = current->next;  
                    }
                    delete current; 
                    num_elements--; 
                    return true; 
                }
                prev = current; 
                current = current->next; 
            }
            return false; 
        }
        
        size_t size() const {
            return num_elements; 
        }

}; 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
   



    return 0; 
}
