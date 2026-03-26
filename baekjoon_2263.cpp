#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct TraversalRange {
    int inorderLeft;
    int inorderRight;
    int postorderLeft;
    int postorderRight;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int nodeCount;
    cin >> nodeCount;

    vector<int> inorderTraversal(nodeCount);
    vector<int> postorderTraversal(nodeCount);

    for (int index = 0; index < nodeCount; ++index) {
        cin >> inorderTraversal[index];
    }

    for (int index = 0; index < nodeCount; ++index) {
        cin >> postorderTraversal[index];
    }


    vector<int> inorderIndexByValue(nodeCount + 1);
    for (int index = 0; index < nodeCount; ++index) {
        inorderIndexByValue[inorderTraversal[index]] = index;
    }

    vector<int> preorderTraversalResult;
    preorderTraversalResult.reserve(nodeCount);

    stack<TraversalRange> traversalRangeStack;
    traversalRangeStack.push({ 0, nodeCount - 1, 0, nodeCount - 1 });

    while (!traversalRangeStack.empty()) {
        TraversalRange currentRange = traversalRangeStack.top();
        traversalRangeStack.pop();

        if (currentRange.inorderLeft > currentRange.inorderRight ||
            currentRange.postorderLeft > currentRange.postorderRight) {
            continue;
        }

        int rootValue = postorderTraversal[currentRange.postorderRight];
        preorderTraversalResult.push_back(rootValue);

        int rootIndexInInorder = inorderIndexByValue[rootValue];
        int leftSubtreeNodeCount = rootIndexInInorder - currentRange.inorderLeft;
        int rightSubtreeNodeCount = currentRange.inorderRight - rootIndexInInorder;


        if (rightSubtreeNodeCount > 0) {
            traversalRangeStack.push({
                rootIndexInInorder + 1,
                currentRange.inorderRight,
                currentRange.postorderLeft + leftSubtreeNodeCount,
                currentRange.postorderRight - 1
                });
        }

        // 왼쪽 서브트리
        if (leftSubtreeNodeCount > 0) {
            traversalRangeStack.push({
                currentRange.inorderLeft,
                rootIndexInInorder - 1,
                currentRange.postorderLeft,
                currentRange.postorderLeft + leftSubtreeNodeCount - 1
                });
        }
    }

    for (int index = 0; index < nodeCount; ++index) {
        cout << preorderTraversalResult[index];
        if (index + 1 < nodeCount) {
            cout << ' ';
        }
    }
    cout << '\n';

    return 0;
}