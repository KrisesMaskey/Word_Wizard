#ifndef map
#include <string>
#include<iostream>
using namespace std;


//AVL Tree Class
template <typename T>
class AVL{
    public:
        //Node Class
        class node{
        public:
            T key;              //Entry
            int height;         //Height of Node
            node * left;        //Left Child
            node * right;       //Right Child

            //Constructor
            node(T k){
                height = 1;
                key = k;
                left = NULL;
                right = NULL;
            }
        };
        node *root = NULL;
        int n;
        void insert(T elem){                   //Method to Insert entry 
            root = INSERT(root, elem);
        }
        void remove(T elem){                   //Method to remove entry
            root = REMOVE(root, elem);
        }
        T search(string elem){                 //Method to Search entry based on key
            return SEARCH(root,elem);
        }
        bool empty(){                       //Check if tree is empty or not
            return isEMPTY(root);
        }
        void increment(string elem){           //Method that increments the value of the entry
            INCREMENT(root, elem);
        }

    
    private:
        //Return Height
        int height(node * head){
            if(head==NULL) return 0;
            return head->height;
        }

        //Right Rotation
        node * rightRotation(node * head){
            node * newhead = head->left;
            head->left = newhead->right;
            newhead->right = head;
            head->height = 1+max(height(head->left), height(head->right));
            newhead->height = 1+max(height(newhead->left), height(newhead->right));
            return newhead;
        }

        //Left Rotation
        node * leftRotation(node * head){
            node * newhead = head->right;
            head->right = newhead->left;
            newhead->left = head;
            head->height = 1+max(height(head->left), height(head->right));
            newhead->height = 1+max(height(newhead->left), height(newhead->right));
            return newhead;
        }

        //Insert entry
        node * INSERT(node * head, T elem){
            if(head==NULL){
                n+=1;
                node * temp = new node(elem);
                return temp;
            }

            //Validate insert location
            if(elem.key < head->key.key) head->left = INSERT(head->left, elem);
            else if(elem.key > head->key.key) head->right = INSERT(head->right, elem);
            
            //Increment height
            head->height = 1 + max(height(head->left), height(head->right));
            int bal = height(head->left) - height(head->right);
            
            //Balance Tree 
            if(bal>1){
                if(elem.key < head->left->key.key){
                    return rightRotation(head);
                }else{
                    head->left = leftRotation(head->left);
                    return rightRotation(head);
                }
            }else if(bal<-1){
                if(elem.key > head->right->key.key){
                    return leftRotation(head);
                }else{
                    head->right = rightRotation(head->right);
                    return leftRotation(head);
                }
            }
            return head;
        }

        //Remove entry
        node * REMOVE(node * head, T elem){
            if(head==NULL) return NULL;

            //Validate location to remove element
            if(elem < head->key){
                head->left = REMOVE(head->left, elem);
            }else if(elem > head->key){
                head->right = REMOVE(head->right, elem);
            }else{
                node * r = head->right;
                if(head->right==NULL){
                    node * l = head->left;
                    delete(head);
                    head = l;
                }else if(head->left==NULL){
                    delete(head);
                    head = r;
                }else{
                    while(r->left!=NULL) r = r->left;
                    head->key = r->key;
                    head->right = REMOVE(head->right, r->key);
                }
            }
            if(head==NULL) return head;

            //Update height
            head->height = 1 + max(height(head->left), height(head->right));
            
            //Balance Tree
            int bal = height(head->left) - height(head->right);
            if(bal>1){
                if(height(head->left) >= height(head->right)){
                    return rightRotation(head);
                }else{
                    head->left = leftRotation(head->left);
                    return rightRotation(head);
                }
            }else if(bal < -1){
                if(height(head->right) >= height(head->left)){
                    return leftRotation(head);
                }else{
                    head->right = rightRotation(head->right);
                    return leftRotation(head);
                }
            }
            return head;
        }

        //Search entry based on key
        T SEARCH(node * head, string val){
            if(head == NULL) return T("*NULL*", -1);
            T k = head->key;
            if(k.key == val) return k;
            if(k.key > val) return SEARCH(head->left, val);
            if(k.key < val) return SEARCH(head->right, val);
        }

        //Increment value of entry
        void INCREMENT(node* head, string val){
            if(head == NULL) return;
            T k = head->key;
            if(k.key == val){ 
                int cnt = head->key.value;
                head->key.value = (cnt + 1);
                return; 
            }  
            if(k.key > val) INCREMENT(head->left, val);
            if(k.key < val) INCREMENT(head->right, val);
        }

        //Return if entry is empty or not
        bool isEMPTY(node* n){
            if (n == NULL)
                return true;
            return false;
        }

};

#endif