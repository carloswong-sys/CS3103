// Michael-Scott Non-blocking Queue algorithm
// Implementation assisted by LLM.

#include <atomic>

using namespace std;

struct Node
{
    double* frame;
    atomic<Node*> next;
    Node(double* f = nullptr) : frame(f), next(nullptr) {}
};

struct MSQueue
{
    atomic<Node*> head;
    atomic<Node*> tail;

    MSQueue()
    {
        Node* dummy = new Node();
        head.store(dummy);
        tail.store(dummy);
    }

    ~MSQueue()
    {
        while (dequeue() != nullptr) {}
        Node* dummy = head.load();
        if (dummy) delete dummy;
    }

    bool enqueue(double* frame) {
        Node* node = new Node(frame);
        Node* last, *next;
        while (true) {
            last = tail.load(memory_order_acquire);
            next = last->next.load(memory_order_acquire);
            if (last == tail.load(memory_order_acquire))
            {
                if (next == nullptr)
                {
                    if (last->next.compare_exchange_weak(next, node, memory_order_release))
                    {
                        tail.compare_exchange_strong(last, node, memory_order_release);
                        return true;
                    }
                }
                else
                {
                    tail.compare_exchange_strong(last, next, memory_order_release);
                }
            }
        }
    }

    double* dequeue()
    {
        Node* first, *last, *next;
        double* result;

        while (true)
        {
            first = head.load(memory_order_acquire);
            last = tail.load(memory_order_acquire);
            next = first->next.load(memory_order_acquire);

            if (first == head.load(memory_order_acquire))
            {
                if (first == last)
                {
                    if (next == nullptr)
                        return nullptr;
                    tail.compare_exchange_strong(last, next, memory_order_release);
                }
                else
                {
                    result = next->frame;
                    if (head.compare_exchange_weak(first, next, memory_order_release))
                    {
                        delete first;
                        return result;
                    }
                }
            }
        }
    }

    double* get_noDequeue()
    {
        Node* first = head.load(memory_order_acquire);
        Node* next = first->next.load(memory_order_acquire);
        return (next != nullptr) ? next->frame : nullptr;
    }

    bool empty()
    {
        Node* first = head.load(memory_order_acquire);
        Node* next = first->next.load(memory_order_acquire);
        return next == nullptr;
    }

    bool full()
    {
        // Flow control handled by semaphores
        return false;
    }
};
