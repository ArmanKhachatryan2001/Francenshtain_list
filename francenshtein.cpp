#include <iostream>
#include <initializer_list>

template <typename T>
class List {
private:
struct Node {
    Node(T val = T(), Node* next = nullptr, Node* prev = nullptr, Node* max = nullptr, Node* min = nullptr) {
        m_value = val;
        m_next = next;
        m_prev = prev;
        m_max = max;
        m_min = min;
    }
    T m_value;
    Node* m_next;
    Node* m_prev;
    Node* m_max;
    Node* m_min;
};
public:
    List();
    List(List&&);
    List(const List<T>&);
    List<T>& operator=(List<T>&&);
    bool operator==(List<T>&);
    bool operator!=(List<T>&);
    List(std::initializer_list<T>);
    List<T>& operator=(const List<T>&);
    template<typename T1>
    friend std::ostream& operator<<(std::ostream& cout, const List<T1>&);
    ~List();
public:
    int size();
    void clear();
    void print();
    void reverse();
    void pop_back();
    void pop_front();
    void resize(int index);
    void push_back(T val);
    void push_front(T val);
    void insert(int index, T value);
    void putinSortedOrder(Node* obj);
    void delegetingNode(Node* obj);
    void assign(int count, const T& value);

private:
    Node* m_head;
    Node* m_tail;
    Node* max_head;
    Node* min_head;
    int m_size;
};

int main(){

}

template<typename T>
void List<T>::assign(int count, const T& value)
{
    if (m_head != nullptr && count > 0) {
        clear();
        m_head = nullptr;
    }
    for (int i = 0; i < count; ++i) {
        push_back(value);
    }
}

template<typename T>
void List<T>::resize(int index)
{
    int new_size = 0;
    if (m_size > index) {
        new_size = m_size;
    }
    if (m_size < index) {
        new_size = m_size;
    }
    while (index < new_size) {
        pop_back();
        --new_size;
    }
    while (index > new_size) {
        push_back(0);
        ++new_size;
    }
}

template<typename T>
void List<T>::pop_front()
{
    if (m_head == m_tail) {
        delete m_head;
        m_head = nullptr;
        m_tail = nullptr;
        max_head = nullptr;
        min_head = nullptr;
        m_size = 0;
    }
    Node* ptr = m_head;
    m_head = m_head->m_next;
    delegetingNode(ptr);
    ptr->m_next = nullptr;
    m_head->m_prev = nullptr;
    delete ptr;
    ptr = nullptr;
    --m_size;
}


template<typename T>
void List<T>::pop_back()
{
    if (m_head == m_tail) {
        delete m_head;
        m_head = nullptr;
        m_tail = nullptr;
        min_head = nullptr;
        max_head = nullptr;
        m_size = 0;
        return;
    }
    Node* ptr = m_tail;
    m_tail = m_tail->m_prev;
    delegetingNode(ptr);
    ptr->m_prev = nullptr;
    m_tail->m_next = nullptr;
    delete ptr;
    ptr = nullptr;
    --m_size;
}

template<typename T>
void List<T>::reverse() {
if (m_head == nullptr || m_size == 1) {
        return;
    } else {
        Node* new_node = m_head;
        Node* node = m_tail;
        Node* end = nullptr;
        while (new_node != node) {
            m_head = m_head->m_next;
            m_head->m_prev = nullptr;
            new_node->m_next = nullptr;
            if (m_tail->m_next == nullptr) {
                m_tail->m_next = new_node;
                new_node->m_prev = m_tail;
                end = new_node;
            } else {
                m_tail->m_next->m_prev = new_node;
                new_node->m_prev = m_tail;
                new_node->m_next = m_tail->m_next;
                m_tail->m_next = new_node;
            }
            new_node = nullptr;
            new_node = m_head;
        }
        m_tail = end;
        end = nullptr;
        new_node = nullptr;
        node = nullptr;
    }
}

template<typename T>
void List<T>::insert(int index, T value)
{
    if (m_head == nullptr && index != 0) {
        std::cout << "Error no index:" << std::endl;
        exit(0);
    }
    if (index == 0) {
        push_front(value);
        return;
    }
    if (index == m_size) {
        push_back(value);
        return;
    }
    Node* ptr = m_head;
    int i = 1;
    while (ptr != nullptr && i < index) {
        ptr = ptr->m_next;
        ++i;
    }
    Node* new_ptr = new Node(value);
    ptr->m_next->m_prev = new_ptr;
    new_ptr->m_prev = ptr;
    new_ptr->m_next = ptr->m_next;
    ptr->m_next = new_ptr;
    putinSortedOrder(new_ptr);
}

template<typename T>
bool List<T>::operator==(List<T>& obj)
{
    if (m_size != obj.m_size) {
        return false;
    }
    Node* ptr = m_head;
    Node* pt = obj.m_head;
    while (ptr != nullptr) {
        if (ptr->m_value != pt->m_value) {
            return false;
        }
        ptr = ptr->m_next;
        pt = pt->m_next;
    }
    return true;
}

template<typename T>
bool List<T>::operator!=(List<T>& obj)
{
    if (m_size != obj.m_size) {
        return true;
    }
    Node* ptr = m_head;
    Node* pt = obj.m_head;
    while (ptr != nullptr) {
        if (ptr->m_value != pt->m_value) {
            return true;
        }
        ptr = ptr->m_next;
        pt = pt->m_next;
    }
    return false;
}

template<typename T>
List<T>& List<T>::operator=(List<T>&& obj)
{
    if (m_head != nullptr) {
        clear();
    } else {
        m_head = obj.m_head;
        m_tail = obj.m_tail;
        max_head = obj.max_head;
        min_head = obj.min_head;
        m_size = obj.m_size;
        obj.m_head = nullptr;
        obj.m_tail = nullptr;
        obj.max_head = nullptr;
        obj.min_head = nullptr;
        obj.m_size = 0;
    }
    return *this;
}

template<typename T>
List<T>& List<T>::operator=(const List<T>& obj)
{
    if (m_head != nullptr) {
        clear();
    }
    if (obj.m_head == nullptr) {
        return *this;
    } else {
        Node* ptr = obj.m_head;
        while (ptr != nullptr) {
            push_back(ptr->m_value);
            ptr = ptr->m_next;
        }
    }
    return *this;
}

template<typename T>
List<T>::List(std::initializer_list<T> obj)
{
    m_head = nullptr;
    m_tail = nullptr;
    max_head = nullptr;
    min_head = nullptr;
    m_size = 0;
    for (auto it = obj.begin(); it != obj.end(); ++it) {
        push_back(*it);
    }
}

template<typename T>
List<T>::List(List<T>&& obj) :
    m_head(obj.m_head),
    m_tail(obj.m_tail),
    max_head(obj.max_head),
    min_head(obj.min_head),
    m_size(obj.m_size)
{
    obj.m_head = nullptr;
    obj.m_tail = nullptr;
    obj.max_head = nullptr;
    obj.min_head = nullptr;
    obj.m_size = 0;
}

template<typename T>
List<T>::List(const List<T>& obj)
{
    if (obj.m_head == nullptr) {
        m_head = nullptr;
    } else {
        Node* new_ptr = obj.m_head;
        m_head = new Node(new_ptr->m_value);
        m_tail = m_head;
        max_head = m_head;
        min_head = m_head;
        new_ptr = new_ptr->m_next;
        Node* H_ptr = m_head;
        while (new_ptr != nullptr) {
            Node* ptr = new Node(new_ptr->m_value);
            ptr->m_prev = H_ptr;
            H_ptr->m_next = ptr;
            H_ptr = H_ptr->m_next;
            putinSortedOrder(ptr);
            ++m_size;
            new_ptr = new_ptr->m_next;
        }
        ++m_size;
    }
}

template<typename T>
std::ostream& operator<<(std::ostream& cout, const List<T>& obj)
{
    typename List<T>::template Node* tmp = obj.m_head;
    while (tmp != nullptr) {
        cout << tmp->m_value << " ";
        tmp = tmp->m_next;
    }
    return cout;
}

template<typename T>
void List<T>::print()
{
    Node* new_ptr = m_head;
    while (new_ptr != nullptr) {
        std::cout << new_ptr->m_value << " ";
        new_ptr = new_ptr->m_next;
    }
    new_ptr = nullptr;
    std::cout << std::endl;
    new_ptr = min_head;
    while (new_ptr != nullptr) {
        std::cout << new_ptr->m_value << " ";
        new_ptr = new_ptr->m_max;
    }
    new_ptr = nullptr;
    std::cout << std::endl;
    new_ptr = max_head;
    while (new_ptr != nullptr) {
        std::cout << new_ptr->m_value << " ";
        new_ptr = new_ptr->m_min;
    }
}

template<typename T>
void List<T>::putinSortedOrder(Node* obj)
{
    if (max_head->m_value <= obj->m_value) {
        max_head->m_max = obj;
        obj->m_min = max_head;
        max_head = obj;
        return;
    }
    if (min_head->m_value >= obj->m_value) {
        min_head->m_min = obj;
        obj->m_max = min_head;
        min_head = obj;
        return;
    }
    Node* new_ptr = min_head;
     while (new_ptr->m_value < obj->m_value) {
        new_ptr = new_ptr->m_max;
     }
     obj->m_max = new_ptr;
     obj->m_min = new_ptr->m_min;
     new_ptr->m_min->m_max = obj;
     new_ptr->m_min = obj;
}
template<typename T>
void List<T>::delegetingNode(Node* obj)
{
    if (max_head->m_value == obj->m_value) {
        max_head = max_head->m_min;
        max_head->m_max = nullptr;
        return;
    }
    if (min_head->m_value == obj->m_value) {
        min_head = min_head->m_max;
        min_head->m_min = nullptr;
        return;
    }
    Node* ptr = min_head;
    while (ptr->m_value < obj->m_value) {
        ptr = ptr->m_max;
    }
    ptr->m_max->m_min = ptr->m_min;
    ptr->m_max->m_min->m_max = ptr->m_max;
    ptr->m_min = nullptr;
    ptr->m_max = nullptr;
}
template<typename T>
void List<T>::push_back(T val)
{
    if (m_head == nullptr) {
        m_head = new Node(val);
        m_tail = m_head;
        max_head = m_head;
        min_head = m_head;
    } else {
        Node* new_ptr = new Node(val);
        new_ptr->m_prev = m_tail;
        m_tail->m_next = new_ptr;
        m_tail = new_ptr;
        putinSortedOrder(new_ptr);
    }
    ++m_size;
}

template<typename T>
void List<T>::push_front(T val)
{
    if (m_head == nullptr) {
        m_head = new Node(val);
        m_tail = m_head;
        max_head = m_head;
        min_head = m_head;
    } else {
        Node* new_ptr = new Node(val);
        m_head->m_prev = new_ptr;
        new_ptr->m_next = m_head;
        m_head = new_ptr;
        putinSortedOrder(new_ptr);
    }
    ++m_size;
}

template<typename T>
void List<T>::clear()
{
     Node* ptr = min_head;
    while (ptr != nullptr) {
        min_head = min_head->m_max;
        ptr->m_max = nullptr;
        ptr = min_head;
    }
    ptr = max_head;
    while (ptr != nullptr) {
        max_head = max_head->m_min;
        ptr->m_min = nullptr;
        ptr = max_head;
    }
    ptr = m_head;
    while (ptr != nullptr) {
        m_head = m_head->m_next;
        delete ptr;
        ptr = nullptr;
        ptr = m_head;
    }
    m_size = 0;
}

template<typename T>
List<T>::List() :
    m_head(nullptr),
    m_tail(nullptr),
    max_head(nullptr),
    min_head(nullptr),
    m_size(0)
{}

template<typename T>
int List<T>::size()
{
    return m_size;
}

template<typename T>
List<T>::~List()
{
    clear();
}
