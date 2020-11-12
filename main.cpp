#include <iostream>
#include <memory> // for make_unique
using namespace std;

class BinaryTreeNode
{
public:
    int value_;
    BinaryTreeNode* left_;
    BinaryTreeNode* right_;

    BinaryTreeNode(int value) :
        value_(value),
        left_(nullptr),
        right_(nullptr)
    {
    }

    ~BinaryTreeNode()
    {
        delete left_;
        delete right_;
    }

    BinaryTreeNode * insertLeft(int value)
    {
        this->left_ = new BinaryTreeNode(value);
        return this->left_;
    }

    BinaryTreeNode * insertRight(int value)
    {
        this->right_ = new BinaryTreeNode(value);
        return this->right_;
    }
};

int findLargest(const BinaryTreeNode* rootNode)
{
    if (rootNode->right_)  {
        return findLargest(rootNode->right_);
    }
    return rootNode->value_;
}

int findSecondLargest(const BinaryTreeNode* rootNode)
{
    if (!rootNode || (!rootNode->left_ && !rootNode->right_)) {
        throw invalid_argument("Tree must have at least 2 nodes");
    }

    // case: we're currently at largest, and largest has a left subtree,
    // so 2nd largest is largest in said subtree
    if (rootNode->left_ && !rootNode->right_) {
        return findLargest(rootNode->left_);
    }

    // case: we're at parent of largest, and largest has no left subtree,
    // so 2nd largest must be current node
    if (rootNode->right_
            && !rootNode->right_->left_
            && !rootNode->right_->right_) {
        return rootNode->value_;
    }

    // otherwise: step right
    return findSecondLargest(rootNode->right_);
}

int main() {
    auto root = make_unique<BinaryTreeNode>(50);
    root->insertLeft(30)->insertLeft(10);
    root->insertRight(70)->insertRight(80);
    root->left_->insertRight(40);
    root->right_->insertLeft(60);
    // cout << root->value_;
    if (findSecondLargest(root.get()) == 70) { cout<< " True"; }
}



/*
     const lest::test tests[] = {
    {CASE("Full tree") {
        auto root = make_unique<BinaryTreeNode>(50);
        root->insertLeft(30)->insertLeft(10);
        root->insertRight(70)->insertRight(80);
        root->left_->insertRight(40);
        root->right_->insertLeft(60);
        EXPECT(findSecondLargest(root.get()) == 70);
    }},
    {CASE("Largest has a left child") {
        auto root = make_unique<BinaryTreeNode>(50);
        root->insertLeft(30)->insertLeft(10);
        root->insertRight(70)->insertLeft(60);
        root->left_->insertRight(40);
        EXPECT(findSecondLargest(root.get()) == 60);
    }},
    {CASE("Largest has a left subtree") {
        auto root = make_unique<BinaryTreeNode>(50);
        root->insertLeft(30)->insertLeft(10);
        root->left_->insertRight(40);
        root->insertRight(70)->insertLeft(60)->insertLeft(55)->insertRight(58);
        root->right_->left_->insertRight(65);
        EXPECT(findSecondLargest(root.get()) == 65);
    }},
    {CASE("Second largest is root node") {
        auto root = make_unique<BinaryTreeNode>(50);
        root->insertLeft(30)->insertLeft(10);
        root->insertRight(70);
        root->left_->insertRight(40);
        EXPECT(findSecondLargest(root.get()) == 50);
    }},
    {CASE("Descending linked list") {
        auto root = make_unique<BinaryTreeNode>(50);
        root->insertLeft(40)->insertLeft(30)->insertLeft(20)->insertLeft(10);
        EXPECT(findSecondLargest(root.get()) == 40);
    }},
    {CASE("Ascending linked list") {
        auto root = make_unique<BinaryTreeNode>(50);
        root->insertRight(60)->insertRight(70)->insertRight(80);
        EXPECT(findSecondLargest(root.get()) == 70);
    }},
    {CASE("Exception when tree has one node") {
        auto root = make_unique<BinaryTreeNode>(50);
        EXPECT_THROWS(findSecondLargest(root.get()));
    }},
    {CASE("Exception when tree is empty") {
        EXPECT_THROWS(findSecondLargest(nullptr));
    }},
};
*/