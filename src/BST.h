
// -*- Mode: c++; --*-

#ifndef _BST_H_
#define _BST_H_

#include <iostream>
#include <stack>
#include <queue>
using namespace std;

template <class Comparable>
class BSTItrIn;

template <class Comparable>
class BST;

template <class Comparable>
class BinaryNode
{
  const Comparable *element;
  BinaryNode *left;
  BinaryNode *right;
  
  BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt )
    :left( lt ), right( rt ) { element = &theElement; }
    
  friend class BST<Comparable>;
  friend class BSTItrIn<Comparable>;
};

template <class Comparable>
class BST
{
 public:
  explicit BST( const Comparable & notFound );
  ~BST( );
  
  const Comparable & findMin( ) const;
  const Comparable & findMax( ) const;
  bool isEmpty( ) const;
  void printTree( ) const;
  
  void makeEmpty( );
  void insert( const Comparable & x );
  void remove( const Comparable & x );
  
 private:
  BinaryNode<Comparable> *root;
  const Comparable ITEM_NOT_FOUND;
  
  const Comparable & elementAt( BinaryNode<Comparable> *t ) const;
  
  void insert( const Comparable & x, BinaryNode<Comparable> * & t ) const;
  void remove( const Comparable & x, BinaryNode<Comparable> * & t ) const;
  BinaryNode<Comparable> * findMin( BinaryNode<Comparable> *t ) const;
  BinaryNode<Comparable> * findMax( BinaryNode<Comparable> *t ) const;
  void makeEmpty( BinaryNode<Comparable> * & t ) const;
  void printTree( BinaryNode<Comparable> *t ) const;
  
  friend class BSTItrIn<Comparable>;
};

// Note that all "matching" is based on the < method.

template <class Comparable>
BST<Comparable>::BST( const Comparable & notFound ) :
  root(NULL), ITEM_NOT_FOUND( notFound )
{ }


template <class Comparable>
BST<Comparable>::~BST( )
{
  makeEmpty( );
}

template <class Comparable>
void BST<Comparable>::insert( const Comparable & x )
{
  insert( x, root );
}

template <class Comparable>
void BST<Comparable>::remove( const Comparable & x )
{
  remove( x, root );
}

template <class Comparable>
const Comparable & BST<Comparable>::findMin( ) const
{
  return elementAt( findMin( root ) );
}

template <class Comparable>
const Comparable & BST<Comparable>::findMax( ) const
{
  return elementAt( findMax( root ) );
}

template <class Comparable>
void BST<Comparable>::makeEmpty( )
{
  makeEmpty( root );
}

template <class Comparable>
bool BST<Comparable>::isEmpty( ) const
{
  return root == NULL;
}


template <class Comparable>
void BST<Comparable>::printTree( ) const
{
  if( isEmpty( ) )
    cout << "Empty tree" << endl;
  else
    printTree( root );
}

template <class Comparable>
const Comparable & BST<Comparable>::
elementAt( BinaryNode<Comparable> *t ) const
{
  if( t == NULL )
    return ITEM_NOT_FOUND;
  else
    return *(t->element);
}


template <class Comparable>
void BST<Comparable>::
insert( const Comparable & x, BinaryNode<Comparable> * & t ) const
{
  if( t == NULL )
    t = new BinaryNode<Comparable>( x, NULL, NULL );
  else
  {
	  Comparable appb = *(t->element);
	  if( x < appb )
		  insert( x, t->left );
	  else
	  {
		  Comparable appb = *(t->element);
		  if( appb < x )
			  insert( x, t->right );
		  else
	       ;
	  }
  }
  // Duplicate; do nothing
}

template <class Comparable>
void BST<Comparable>::
remove( const Comparable & x, BinaryNode<Comparable> * & t ) const
{
  Comparable appb = *(t->element);
  if( t == NULL )
    return;   // Item not found; do nothing
  if( x < appb )
    remove( x, t->left );
  else if( appb < x )
    remove( x, t->right );
  else if( t->left != NULL && t->right != NULL ) // Two children
    {
      t->element = findMax( t->right )->element; //rep
      remove( *(t->element), t->right );
    }
  else
    {
      BinaryNode<Comparable> *oldNode = t;
      t = ( t->left != NULL ) ? t->left : t->right;
      delete oldNode;
    }
}

template <class Comparable>
BinaryNode<Comparable> *
BST<Comparable>::findMax( BinaryNode<Comparable> *t ) const //rep
{
  if( t == NULL )
    return NULL;
  if( t->left == NULL )
    return t;
  return findMax( t->left );
}


template <class Comparable>
BinaryNode<Comparable> *
BST<Comparable>::findMin( BinaryNode<Comparable> *t ) const
{
  if( t != NULL )
    while( t->right != NULL )
      t = t->right;
  return t;
}
/****** NONRECURSIVE VERSION*************************
        template <class Comparable>
        BinaryNode<Comparable> *
        BST<Comparable>::
        find( const Comparable & x, BinaryNode<Comparable> *t ) const
        {
            while( t != NULL )
                if( x < t->element )
                    t = t->left;
                else if( t->element < x )
                    t = t->right;
                else
                    return t;    // Match
            return NULL;   // No match
        }
*****************************************************/

/**
 * Internal method to make subtree empty.
 */
template <class Comparable>
void BST<Comparable>::
makeEmpty( BinaryNode<Comparable> * & t ) const
{
  if( t != NULL )
    {
      makeEmpty( t->left );
      makeEmpty( t->right );
      delete t;
    }
  t = NULL;
}



/**************
// Iteradores
**************/

template <class Comparable>
class BSTItrIn {
public:
  BSTItrIn(const BST<Comparable> &bt);
  
  void advance();
  const Comparable * retrieve() { return itrStack.top()->element; }
  bool isAtEnd() {return itrStack.empty(); }

private:
  stack<BinaryNode<Comparable> *> itrStack;

  void slideLeft(BinaryNode<Comparable> *n);
};

template <class Comparable>
BSTItrIn<Comparable>::BSTItrIn (const BST<Comparable> &bt)
{
  if (!bt.isEmpty())
    slideLeft(bt.root);
}

template <class Comparable>
void BSTItrIn<Comparable>::slideLeft(BinaryNode<Comparable> *n)
{
  while (n) {
    itrStack.push(n);
    n = n->left;
  }
}

template <class Comparable>
void BSTItrIn<Comparable>::advance()
{
  BinaryNode<Comparable> * actual = itrStack.top();
  itrStack.pop();
  BinaryNode<Comparable> * seguinte = actual->right;
  if (seguinte)
    slideLeft(seguinte);
}

#endif
