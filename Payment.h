#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <vector>
using namespace std;

struct Payment {
    string paymentId;
    string username;
    string tenancyId;
    string amount;
    string date;
    string status;
};

struct PaymentLinkedList {
    Payment data;
    PaymentLinkedList* prev;
    PaymentLinkedList* next;

    void insertNewPayment(PaymentLinkedList** payment_head, string id, string uname, string tenancy, string amount, string date, string stat){
        PaymentLinkedList* newPayment = new PaymentLinkedList;
        newPayment->data.paymentId = id;
        newPayment->data.username = uname;
        newPayment->data.tenancyId = tenancy;
        newPayment->data.amount = amount;
        newPayment->data.date = date;
        newPayment->data.status = stat;
        newPayment->prev = nullptr;
        newPayment->next = nullptr;

        if (*payment_head == nullptr) {
            *payment_head = newPayment;
            
        } else {
            PaymentLinkedList* current = *payment_head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newPayment;
            newPayment->prev = current;
        }
    }

    string generatePaymentId(PaymentLinkedList* payment_root) {
        int count = 0;
        PaymentLinkedList* current = payment_root;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return "P0" + to_string(count + 1);
    }

    void modifyPaymentStatus(PaymentLinkedList** head, string paymentId, string status) {
        PaymentLinkedList* current = *head;
        while (current != nullptr) {
            if (current->data.paymentId == paymentId) {
                current->data.status = status;
                break;
            }
            current = current->next;
        }
    }
    
};