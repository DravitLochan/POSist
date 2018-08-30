#include <iostream>
#include <string>
#include <string.h>
#include <time.h>
#include <vector>

using namespace std;

int global_node_number;
time_t time_helper;
string current_time;

struct DataOfNode {
    string owner_id;
    float value;
    string owner_name;
    string hash;
};

struct TreeNode {
    string timestamp;
    DataOfNode data;
    int node_number;
    string node_id;
    string parent_node_id;
    vector <string> child_reference_node_id;
    string gensis_node_id;
    string hash_value;
};

struct MasterListNode {
    TreeNode *gensis_node;
    MasterListNode *next;
};

string getCurrentTime(){
    time_helper = time(NULL);
    return ctime(&time_helper);
}

MasterListNode * createMasterListNode(){
    MasterListNode *ptr =  new MasterListNode;
    ptr -> next = NULL;
    return ptr;
}


TreeNode * createTreeNode(bool isGensis, DataOfNode data){
    TreeNode *ptr = new TreeNode;           // create a tree node
    current_time = getCurrentTime();
    ptr -> timestamp = current_time;        // assign current time to the node
    if(isGensis){
        ptr -> parent_node_id = "NULL";
    }
    ptr -> data = data;
    ptr -> node_number = global_node_number++;
    return ptr;
}


void createGensisNode(MasterListNode *master_list_head){
    MasterListNode *current_gensis_node = createMasterListNode();
    DataOfNode input_data;
    cout << "Create Gensis Node # " << global_node_number << ":\n";
    cout << "Enter Owner id, Owner Name and Value of the Node:\n";
    cin >> input_data.owner_id >> input_data.owner_name >> input_data.value;
    TreeNode *input_node = createTreeNode(true, input_data);
    current_gensis_node -> gensis_node = input_node;
    while(master_list_head -> next != NULL)
        master_list_head = master_list_head -> next;
    master_list_head -> next = current_gensis_node;
    return ;
}

TreeNode * findNode(MasterListNode *master_list_head, int parent_num){
    while(master_list_head -> next){
        if(master_list_head -> next && master_list_head -> next -> gensis_node -> node_number > parent_num)
            master_list_head = master_list_head -> next;
        else if(!master_list_head -> next){
            return NULL;
        } else {

        }
    }
}

void createSeetOfChildNodesOfAPrticularNode(MasterListNode *master_list_head){
    int parent_num, num_of_children, value_of_parent;
    DataOfNode input_data;
    cout << "Enter the parent node number and number of children you want to create\n";
    cin >> parent_num >> num_of_children;
    TreeNode *parent = findNode(master_list_head, parent_num);
    value_of_parent = parent -> data.value;
    for(int i = 0; i < num_of_children; ++i){

    }
}

MasterListNode * init(){
    MasterListNode *ptr = createMasterListNode();
    global_node_number = 0;
    return ptr;
}
int main() {
	MasterListNode *master_list_head = init();
	cout << "Head node created successfully!\n";                    // head node is just a dummy node. it's next contains address to first gensis node
    int choice;
    cout << "Select an option from the menu\n1. Create a Gensis Node\n2. Create Set of Child Nodes of a Particular Node\n";
    cin >> choice;
    while(choice){
        switch(choice){
            case 1:
                createGensisNode(master_list_head);
                break;
            case 2:
                createSeetOfChildNodesOfAPrticularNode(master_list_head);
                break;
        }
        cin >> choice;
    }
    cout << "\n\nThank You\n";
	return 0;
}
