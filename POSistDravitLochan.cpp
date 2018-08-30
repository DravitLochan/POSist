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
    TreeNode *node_id;
    TreeNode *parent_node_id;
    vector <TreeNode *> child_reference_node_id;
    TreeNode *gensis_node_id;
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


TreeNode * createTreeNode(DataOfNode data, TreeNode *parent = NULL){
    TreeNode *ptr = new TreeNode;           // create a tree node
    current_time = getCurrentTime();
    ptr -> timestamp = current_time;        // assign current time to the node
    ptr -> parent_node_id = parent;
    ptr -> data = data;
    ptr -> node_number = global_node_number++;
    return ptr;
}


void createGensisNode(MasterListNode *master_list_head){
    MasterListNode *current_gensis_node = createMasterListNode();
    DataOfNode input_data;
    cout << "Create Gensis Node # " << global_node_number + 1 << ":\n";
    cout << "Enter Owner id, Owner Name and Value of the Node:\n";
    cin >> input_data.owner_id >> input_data.owner_name >> input_data.value;
    TreeNode *input_node = createTreeNode(input_data);
    input_node -> node_id = input_node;
    input_node -> gensis_node_id = input_node;
    current_gensis_node -> gensis_node = input_node;
    while(master_list_head -> next != NULL)
        master_list_head = master_list_head -> next;
    master_list_head -> next = current_gensis_node;
    cout << "Gensis Node created successfully!\n";
    return ;
}

TreeNode * findNode(MasterListNode *master_list_head, int parent_num){
    master_list_head = master_list_head -> next;
    while(master_list_head){
        TreeNode *ptr = master_list_head->gensis_node;
        vector <TreeNode *> children = ptr->child_reference_node_id;
        for(int i = 0; i < children.size(); ++i){
            if(parent_num == children[i]->node_number)
                return children[i];
        }
        master_list_head = master_list_head->next;
    }
    return NULL;
}


void createSeetOfChildNodesOfAPrticularNode(MasterListNode *master_list_head){
    int parent_num, num_of_children, value_of_parent, sum_of_children = 0;
    DataOfNode input_data;
    cout << "Enter the parent node number and number of children you want to create\n";
    cin >> parent_num >> num_of_children;
    TreeNode *parent = findNode(master_list_head, parent_num);
    if(!parent){
        cout << "No parent with given node found!\n";
        return ;
    }
    vector <TreeNode *> children = parent->child_reference_node_id;
    for(int i = 0; i < children.size(); ++i){
        sum_of_children += children[i]->data.value;
    }
    value_of_parent = parent -> data.value;
    TreeNode *child;
    for(int i = 0; i < num_of_children; ++i){
        cout << "Enter owner id, value and owner name for child # " << i+1 <<"\n";
        cin >> input_data.owner_id >> input_data.value >> input_data.owner_name;
        if(sum_of_children + input_data.value > value_of_parent){
            cout << "sum of child values = " << sum_of_children << " and value of parent = " << value_of_parent <<
            ". Aborting transaction as the value of children can not be greater than parent's value\n";
            return ;
        }
        sum_of_children += input_data.value;
        child = createTreeNode(input_data, parent);
        parent->child_reference_node_id.push_back(child);
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
