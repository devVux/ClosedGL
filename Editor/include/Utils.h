#pragma once

namespace Tree {

	template <class T>
	struct TreeNode {

		std::vector<TreeNode<T>*> nodes;
		T value;
		bool isLeaf;

		TreeNode(T val, bool leaf = false): value(val), isLeaf(leaf) { }

		~TreeNode() {
			while (!nodes.empty()) {
				delete nodes.back();
				nodes.pop_back();
			}
		}

		void add(T n) {
			nodes.push_back(new Node<T>(n));
		}
		void add(TreeNode<T>* n) {
			nodes.push_back(n);
		}



	};

	template <class T>
	TreeNode<T>* findParent(TreeNode<T>* root, TreeNode<T>* node) {
		if (root == nullptr || node == nullptr)
			return nullptr;
		else if (root == node)
			return root;

		TreeNode<T>* parent = nullptr;
		for (auto& child : root->nodes) {
			parent = findParent(child, node);
			if (parent != nullptr)
				return parent;
		}

		return parent;
	}

	template <class T>
	bool remove(TreeNode<T>* root, TreeNode<T>* node, TreeNode<T>* parent) {

		if (root == nullptr || node == nullptr)
			return false;

		else if (root == node)
			return true;

		int i = 0;
		for (auto& child : root->nodes) {
			if (remove(child, node, root)) {
				delete child;
				root->nodes.erase(std::begin(root->nodes) + i);
				return false;
			}
			i++;
		}

		return false;
	}


}
