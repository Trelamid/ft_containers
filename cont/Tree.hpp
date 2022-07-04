/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 23:10:11 by ncolomer          #+#    #+#             */
/*   Updated: 2020/03/02 17:38:39 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_HPP
# define TREE_HPP

# include <utility>
# include "Iterator.hpp"

namespace ft
{
	enum Color{
		Red, Black
	};
	template <typename K, typename V>
	class Node
	{
	private:

	public:
		Node*	parent;
		Node*	left;
		Node*	right;
		Color	color;
		bool	isLast;
		K		key;
		V		value;
		Node()
		{
			isLast = true;
			parent = NULL;
			left = NULL;
			right = NULL;
			color = Black;
		}
	};



	template <typename K, typename V, class Compare = std::less<K>, typename Alloc = std::allocator<Node<K, V> > >
	class Tree
	{
	public:
		typedef Node<K, V>		node;
		class iterator
		{
		protected:
			node *node1;
			std::pair<K,V> pair;
		public:
			iterator(){
				node1 = NULL;
			}
			iterator(node *node2){
				node1 = node2;
			}
//			iterator(iterator &auf){
//				node1 = auf.node1;
//				pair = auf.pair;
//			}
			~iterator(){
//				delete pair;
			}
			iterator &operator=(iterator auf)
			{
				node1 = auf.node1;
				pair = auf.pair;
				return *this;
			}
			iterator &operator++()
			{
//				std::cout << node1->value;
				if(!node1->isLast && !node1->right->isLast)
				{
					if(!node1->right->left->isLast)
					{
						node1 = node1->right;
						while(!node1->isLast)
							node1= node1->left;
						node1 = node1->parent;
					}
					else
						node1 = node1->right;
				}
				else
				{
					if(node1 == node1->parent->left)
						node1 = node1->parent;
					else if(node1 == node1->parent->right)
					{
						if(node1->key < node1->parent->parent->key)
							node1 = node1->parent->parent;
						else
							node1 = node1->right; //end
					}
				}
				return *this;
			}
			iterator &operator--()
			{
				if(!node1->left->isLast)
				{
					if(!node1->left->right->isLast)
					{
						node1 = node1->left;
						while(!node1->isLast)
							node1= node1->right;
						node1 = node1->parent;
					}
					else
						node1 = node1->left;
				}
				else
				{
					if(node1 == node1->parent->right)
						node1 = node1->parent;
					else if(node1 == node1->parent->left)
					{
						if(node1->key > node1->parent->parent->key)
							node1 = node1->parent->parent;
						else
							return this; //end
					}
				}
				return this;
			}
			std::pair<K,V> &operator*()
			{
				std::pair<K,V> pair1(node1->key, node1->value);
				pair = pair1;
				return pair;
			}
		};

		class reverse_iterator
		{
		protected:
			node *node1;
			std::pair<K,V> pair;
		public:
			reverse_iterator()
			{
				node1 = NULL;
			}
			reverse_iterator(node *node2)
			{
				node1 = node2;
			}
			reverse_iterator(reverse_iterator &auf){
				node1 = auf.node1;
				pair = auf.pair;
			}
			~reverse_iterator(){
				delete pair;
			}
			reverse_iterator &operator=(const reverse_iterator &auf)
			{
				node1 = auf.node1;
				pair = auf.pair;
				return *this;
			}
			reverse_iterator &operator++()
			{
				if(!node1->left->isLast)
				{
					if(!node1->left->right->isLast)
					{
						node1 = node1->left;
						while(!node1->isLast)
							node1= node1->right;
						node1 = node1->parent;
					}
					else
						node1 = node1->left;
				}
				else
				{
					if(node1 == node1->parent->right)
						node1 = node1->parent;
					else if(node1 == node1->parent->left)
					{
						if(node1->key > node1->parent->parent->key)
							node1 = node1->parent->parent;
						else
							node1 = node1->left; //end
					}
				}
				return this;
			}
			reverse_iterator &operator--()
			{
				if(!node1->right->isLast)
				{
					if(!node1->right->left->isLast)
					{
						node1 = node1->right;
						while(!node1->isLast)
							node1= node1->left;
						node1 = node1->parent;
					}
					else
						node1 = node1->right;
				}
				else
				{
					if(node1 == node1->parent->left)
						node1 = node1->parent;
					else if(node1 == node1->parent->right)
					{
						if(node1->key < node1->parent->parent->key)
							node1 = node1->parent->parent;
						else
							return this; //end
					}
				}
				return this;
			}
			std::pair<K,V> &operator*()
			{
				std::pair<K,V> pair1(node1->key, node1->value);
				pair = pair1;
				return pair;
			}
		};

		node *begin()
		{
//			std::cout << "asd";
			node *start = root;
			while (!start->left->isLast)
				start=start->left;
//			return iterator();
//			iterator ita(start);
//			std::cout << "asd";

			return start;
		}
		iterator *end()
		{
			node *start = root;
			while (!start->isLast)
				start=start->right;
			return iterator(start);
		}
		reverse_iterator &rbegin()
		{
			node *start = root;
			while (!start->right->isLast)
				start=start->right;
			return reverse_iterator(start);
		}

		reverse_iterator *rend()
		{
			node *start = root;
			while (!start->isLast)
				start=start->left;
			return reverse_iterator(start);
		}

		Tree(Alloc alloc1 = Alloc()):root(NULL), alloc(alloc1){
			alloc = Alloc();
		}
	protected:
		node* root = NULL;
		int h;
		Alloc alloc;

		void LeftRotate(node *y)
		{
			node *parentY = y->parent;
			node *z = y->right;
			node *x = y->left;

			y->parent = y->right;
			y->right = z->left;
			z->left = y;
			z->parent = parentY;
			y->right->parent = y;

//			y->color = Red;
//			z->color = Black;
//			Color help = y->color;
			z->color = y->color;
			y->color = Red;

			if(parentY)
			{
				if(parentY->right == y)
					parentY->right = z;
				else if(parentY->left == y)
					parentY->left = z;
			}
			else
				root = z;
		}

		void RightRotate(node *y)
		{
			node *parentY = y->parent;
//			node *z = y->right;
			node *x = y->left;

			y->parent = x;
			y->left = x->right;
			x->right = y;
			x->parent = parentY;
			y->left->parent = y;

//			Color help = y->color;
			x->color = y->color;
			y->color = Red;

			if(parentY)
			{
				if(parentY->right == y)
					parentY->right = x;
				else if(parentY->left == y)
					parentY->left = x;
			}
			else
				root = x;
		}

		void swapColor(node *y)
		{
//			std::cout<< "b";

			y->right->color = Black;
			y->left->color = Black;
			if(y != root)
				y->color = Red;
			else
				y->color = Black;
//			if(y != root && y->parent->color == Red)
//			{
////				std::cout<< "c";
//				if(y->parent->parent->right->color == Red)
//					swapColor(y->parent->parent);
//				else
//					RightRotate(y->parent->parent);
//			}
//			std::cout<< "d";
		}

		void forInsert(node newNode)
		{
			if(!root)
			{
//				std::cout << "1";

				root = alloc.allocate(1);
				alloc.construct(root, newNode);

				root->left = alloc.allocate(1);
				alloc.construct(root->left, node());

				root->parent = NULL;

				root->right = alloc.allocate(1);
				alloc.construct(root->right, node());

				root->isLast = false;
				root->left->parent = root;
				root->right->parent = root;
				root->color = Black;

				return;
			}
			else
			{
				node *node2 = root;
				while(!node2->isLast)
				{
//					std::cout << "a";
					if(node2->key > newNode.key)
						node2 = node2->left;
					else if(node2->key < newNode.key)
						node2 = node2->right;
					else
						return;
				}
				node2->left = alloc.allocate(1);
				alloc.construct(node2->left, node());

				node2->right = alloc.allocate(1);
				alloc.construct(node2->right, node());

				node2->left->parent = node2;
				node2->right->parent = node2;

				node2->color = Red;

				node2->isLast = false;
				node2->key = newNode.key;
				node2->value = newNode.value;

//				std::cout << node2->key << node2->parent->key;
				insertBalanc(node2);
			}
		}
		void insertBalanc(node *newNode)
		{
//			std::cout << "\n\n"<<newNode->key;
//			print();
			insertBalancRec(newNode->parent);
		}
		void insertBalancRec(node *y)
		{
			if(y==root)
				root->color = Black;
			if(y && y->left->color == Black && y->right->color == Red)
			{
				LeftRotate(y);
				insertBalancRec(y);
			}
			else if(y && y->color == Red && y->left->color == Red && y->right->color == Black)
			{
				RightRotate(y->parent);
				insertBalancRec(y);
			}
			else if(y && y->left->color == Red && y->right->color == Red)
			{
				swapColor(y);
				insertBalancRec(y->parent);
			}
			if(y==root)
				root->color = Black;
		}
		void forErase(node *deleteNode)
		{
			if(deleteNode->left->isLast && deleteNode->right->isLast)
			{
//				std::cout << "zeroErase";
				zeroErase(deleteNode);

				alloc.destroy(deleteNode->left);
				alloc.deallocate(deleteNode->left, 1);
				alloc.destroy(deleteNode->right);
				alloc.deallocate(deleteNode->right, 1);
				deleteNode->color = Black;
				deleteNode->isLast = true;
			}
			else if(!deleteNode->left->isLast && !deleteNode->right->isLast)
			{
//				std::cout << "twoErase";
				twoErase(deleteNode);
			}
			else if(!deleteNode->left->isLast && deleteNode->right->isLast)
			{
//				std::cout << "oneErase";
				oneErase(deleteNode);
			}
		}
		void zeroErase(node *deleteNode)
		{
//			std::cout << deleteNode->key;

			if(deleteNode->color == Red) //1
			{

			}
			else if(deleteNode->color == Black) // 2
			{
				node *a = deleteNode->parent;
				if(!a)
					return;
//				std::cout << deleteNode->key;
				node *b;
				if (a->left == deleteNode)
				{
					b = a->right;
					if (b->color == Black)
					{
						if (b->right->color == Red || b->left->color == Red)
						{
							Color colA;

							colA = a->color;

							if (b->right->color == Red)
							{
								LeftRotate(a);
								b->color = colA;
								a->color = Black;
								b->right->color = Black;
							}
							else if (b->left->color == Red)
							{
								RightRotate(b);
								b->color = Red;
								b->parent->color = Black;
								b->right->color = Black;

								colA = a->color;

								LeftRotate(a);
								b->color = colA;
								a->color = Black;
								b->right->color = Black;
							}
						}
						else if (b->right->color == Black && b->left->color == Black)
						{
							b->color = Red;
							if (b->parent->color == Red)
								b->parent->color = Black;
							else
								zeroErase(b->parent);
						}
					}
					else if (b->color == Red)
					{
						LeftRotate(a);
						b->color = Black;
						a->color = Red;
						zeroErase(deleteNode);
					}
				}
				else if (a->right == deleteNode) {
					b = a->left;
					if (b->color == Black)
					{
						if (b->right->color == Red || b->left->color == Red) {
							Color colA;

							colA = a->color;

							if (b->right->color == Red)
							{
								RightRotate(a);
								b->color = colA;
								a->color = Black;
								b->left->color = Black;
							}
							else if (b->left->color == Red) {
								LeftRotate(b);
								b->color = Red;
								b->parent->color = Black;
								b->left->color = Black;

								colA = a->color;

								RightRotate(a);
								b->color = colA;
								a->color = Black;
								b->left->color = Black;
							}
						}
						else if (b->right->color == Black && b->left->color == Black)
						{
//							std::cout << "auf";

							b->color = Red;
							if (b->parent->color == Red)
							{
//								std::cout << b->parent->key;

								b->parent->color = Black;
							}
							else
								zeroErase(b->parent);
						}
					}
					else if (b->color == Red)
					{
						RightRotate(a);
						b->color = Black;
						a->color = Red;
						zeroErase(deleteNode);
					}
				}
			}
		}
		void oneErase(node *deleteNode) //3
		{
//			std::cout << " oneErase";
			node *x,*y;
			x = deleteNode;

			if(x->left->isLast)
				y = deleteNode->right;
			else
				y = deleteNode->left;

			y->isLast = true;
			x->key = y->key;
			x->value = y->value;

			alloc.destroy(y->left);
			alloc.deallocate(y->left, 1);
			alloc.destroy(y->right);
			alloc.deallocate(y->right, 1);
			y->isLast = true;
			y->color = Black;

		}
		void twoErase(node *deleteNode) //4
		{
			node *maxLeft;

			maxLeft = deleteNode->left;
			while(!maxLeft->isLast)
				maxLeft = maxLeft->right;
			maxLeft = maxLeft->parent;

			deleteNode->key = maxLeft->key;
			deleteNode->value = maxLeft->value;

			forErase(maxLeft);
		}
	public:
		void print()
		{
//			std::cout << '\n' << '\n'<< h;
//			h += 1;
			print2(root);
			if(!root->left->isLast)
				print2(root->left);
			if(!root->right->isLast)
				print2(root->right);
			print2(root->left->left);
			print2(root->right->left);
		}
		void print2(node *auf)
		{
			std::cout << '\n';
			std::cout << "    "<<auf->key;// <<  auf->value;
			if(auf->color == Black)
				std::cout << "Black";
			else
				std::cout << "Red";
			if(auf->isLast)
				std::cout << " isLast";

			std::cout << "\n" << auf->left->key;// <<  auf->left->value;
			if(auf->left->color == Black)
				std::cout << "Black";
			else
				std::cout << "Red";
			if(auf->left->isLast)
				std::cout << " isLast";

			std::cout << "    " << auf->right->key;// <<  auf->right->value;
			if(auf->right->color == Black)
				std::cout << "Black";
			else
				std::cout << "Red";
			if(auf->right->isLast)
				std::cout << " isLast";
		}
		void insert(K key, V value)
		{

			node newNote;
			newNote.key = key;
			newNote.value = value;
			newNote.color = Red;

//			std::cout << newNote.key;
//			root = alloc.allocate(1);
			forInsert(newNote);
		}
		void erase(K key)
		{
			node *deleteNode = find(key);
			if(deleteNode == NULL)
				throw std::runtime_error("Don`t have this key");
			forErase(deleteNode);
		}

		node *find(K key)
		{
			node *auf = root;
			if(root->isLast)
				return NULL;
			while(auf->key != key && !auf->isLast)
			{
				if(auf->key > key)
					auf = auf->left;
				else if(auf->key < key)
					auf = auf->right;
				else
					return auf;
			}
			if(auf->key == key)
				return auf;
			else
				return NULL;
		}
	};
}

#endif