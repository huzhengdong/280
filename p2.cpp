#include<iostream>
#include<cstdlib>
#include "p2.h"

using namespace std;


int size(list_t list)
{
	if(list_isEmpty(list))
		return 0;
	else
		return 1+size(list_rest(list));
}

bool memberOf(list_t list, int val)
{
	if(list_isEmpty(list))
		return 0;
	else if(val==list_first(list))
		return 1;
	else
		return memberOf(list_rest(list),val);
}

int dot(list_t v1, list_t v2)
{
  if(list_isEmpty(list_rest(v1)) || list_isEmpty(list_rest(v2)))
        return list_first(v1)*list_first(v2);
	else
		return list_first(v1)*list_first(v2)+dot(list_rest(v1),list_rest(v2));
}

bool isIncreasing(list_t v)
{
	if(list_isEmpty(v) || list_isEmpty(list_rest(v)))
		return 1;
	else
		return (list_first(v)<=list_first(list_rest(v))) && isIncreasing(list_rest(v));
}

static list_t
list_lastmake(int elt, list_t list)
{
	if(list_isEmpty(list))
		return list_make(elt,list);
	else
		return list_make(list_first(list),list_lastmake(elt,list_rest(list)));
}

list_t reverse(list_t list)
{
	if(list_isEmpty(list) || list_isEmpty(list_rest(list)))
		return list;
	else
		return list_lastmake(list_first(list),reverse(list_rest(list)));
		
}

list_t append(list_t first, list_t second)
{
	if(list_isEmpty(second))
		return first;
	else if(list_isEmpty(first))
	    return second;
	else
		return append(list_lastmake(list_first(second),first), list_rest(second));
}

bool isArithmeticSequence(list_t v)
{
	if(list_isEmpty(v) || list_isEmpty(list_rest(v))||list_isEmpty(list_rest(list_rest(v))))
		return 1;
	else
		return (list_first(v)-list_first(list_rest(v)))==(list_first(list_rest(v))-list_first(list_rest(list_rest(v))))  
			&& isArithmeticSequence(list_rest(v));
}

list_t filter_odd(list_t list)
{
	if(list_isEmpty(list))
		return list_make();
	else if(list_first(list)%2==0)
		return filter_odd(list_rest(list));
	else
		return list_make(list_first(list),filter_odd(list_rest(list)));
}

list_t filter(list_t list, bool (*fn)(int))
{
	if(list_isEmpty(list))
		return list_make();
	else if(fn(list_first(list))==0)
		return filter(list_rest(list),fn);
	else
		return list_make(list_first(list),filter(list_rest(list),fn));
}

static bool is_nonunique(int elt,list_t v)
{
	if(list_isEmpty(v))
		return 0;
	else
		return elt==list_first(v)||is_nonunique(elt,list_rest(v));
	
}

static list_t
unique_helper(list_t first,list_t second)
{
	if(list_isEmpty(second))
		return first;
	else if(is_nonunique(list_first(second),first))
		return unique_helper(first,list_rest(second));
	else
		return unique_helper(list_lastmake(list_first(second),first),list_rest(second));
}

list_t unique(list_t list)
{
	if(list_isEmpty(list) || list_isEmpty(list_rest(list)) )
		return list;
	else 
		return unique_helper(list_make(),list);
	
}

static list_t first_nElements(unsigned int n,list_t v)
{
    if(n==0)
        return list_make();
	else
		return list_make(list_first(v),first_nElements(n-1,list_rest(v)));
}

static list_t remain_Elements(unsigned int n,list_t v)
{
	if(n==0)
	    return v;
	else
		return remain_Elements(n-1,list_rest(v));
}

list_t insert_list(list_t first, list_t second, unsigned int n)
{
		return append(append(first_nElements(n,first),second),remain_Elements(n,first));
}

list_t chop(list_t list, unsigned int n)
{
    if(n==0)
        return list;
    else if((unsigned int)size(list)==n)
        return list_make();
    else
        return list_make(list_first(list),chop(list_rest(list),n));
}

int tree_sum(tree_t tree)
{
    if(tree_isEmpty(tree))
        return 0;
    else
        return tree_elt(tree)+tree_sum(tree_left(tree))+tree_sum(tree_right(tree));

}

bool tree_search(tree_t tree, int val)
{
    if (tree_isEmpty(tree))
        return 0;
    else
        return tree_elt(tree)==val || tree_search(tree_left(tree),val) || tree_search(tree_right(tree),val);

}

static int max(int a,int b)
{
    if(a>=b)
        return a;
    else
        return b;
}
int depth(tree_t tree)
{
    if(tree_isEmpty(tree))
        return 0;
    else
        return 1+max(depth(tree_left(tree)), depth(tree_right(tree)));
}

int tree_max(tree_t tree)
{
   if(tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_right(tree)))
        return tree_elt(tree);
    else if(!(tree_isEmpty(tree_left(tree))) && tree_isEmpty(tree_right(tree)))
        return max(tree_elt(tree), tree_max(tree_left(tree)));
    else if(tree_isEmpty(tree_left(tree)) && !(tree_isEmpty(tree_right(tree))))
        return max(tree_elt(tree), tree_max(tree_right(tree)));
    else
        return max(tree_elt(tree), max(tree_max(tree_left(tree)),tree_max(tree_right(tree))));

}

list_t traversal(tree_t tree)
{
    if(tree_isEmpty(tree))
        return list_make();
    else
        return append( traversal(tree_left(tree)), list_make(tree_elt(tree),traversal(tree_right(tree))));
}


static bool tree_Monotonical_helper(int elt, tree_t tree)
{
    if(tree_isEmpty(tree))
        return 1;
    if(tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_right(tree)))
        return 1;
    else if(!(tree_isEmpty(tree_left(tree))) && tree_isEmpty(tree_right(tree)))
        return ((elt>=tree_elt(tree))==(tree_elt(tree)>=tree_elt(tree_left(tree))))&&tree_Monotonical_helper(tree_elt(tree),tree_left(tree));
    else if(tree_isEmpty(tree_left(tree)) && !(tree_isEmpty(tree_right(tree))))
        return ((elt>=tree_elt(tree))==(tree_elt(tree)>=tree_elt(tree_right(tree))))&&tree_Monotonical_helper(tree_elt(tree),tree_right(tree));
    else
        return (((elt>=tree_elt(tree))==(tree_elt(tree)>=tree_elt(tree_left(tree))))&&tree_Monotonical_helper(tree_elt(tree),tree_left(tree)))
               || (((elt>=tree_elt(tree))==(tree_elt(tree)>=tree_elt(tree_right(tree))))&&tree_Monotonical_helper(tree_elt(tree),tree_right(tree)));
}

bool tree_hasMonotonicPath(tree_t tree)
{

    if(tree_isEmpty(tree))
        return 0;
    else if(tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_right(tree)))
        return 1;
    else if(!(tree_isEmpty(tree_left(tree))) && tree_isEmpty(tree_right(tree)))
        return tree_Monotonical_helper(tree_elt(tree),tree_left(tree));
    else if(tree_isEmpty(tree_left(tree)) && !(tree_isEmpty(tree_right(tree))))
        return tree_Monotonical_helper(tree_elt(tree),tree_right(tree));
    else
        return	tree_Monotonical_helper(tree_elt(tree),tree_left(tree))
                  || tree_Monotonical_helper(tree_elt(tree),tree_right(tree));

}

bool tree_allPathSumGreater(tree_t tree, int sum)
{
    if(tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_right(tree)))
        return tree_elt(tree)>sum;
    else if(!tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_right(tree)))
        return tree_allPathSumGreater(tree_left(tree),sum-tree_elt(tree));
    else if(tree_isEmpty(tree_left(tree)) && !tree_isEmpty(tree_right(tree)))
        return tree_allPathSumGreater(tree_right(tree),sum-tree_elt(tree));
    else
        return tree_allPathSumGreater(tree_left(tree),sum-tree_elt(tree))
               && tree_allPathSumGreater(tree_right(tree),sum-tree_elt(tree));
}

bool covered_by(tree_t A, tree_t B)
{
    if(tree_isEmpty(A))
        return 1;
    else if(tree_isEmpty(B))
        return 0;
    else if(tree_elt(A)==tree_elt(B))
        return covered_by(tree_left(A),tree_left(B)) && covered_by(tree_right(A),tree_right(B));
    else
        return 0;
}

bool contained_by(tree_t A, tree_t B)
{
    if(tree_isEmpty(A))
        return 1;
    else if(tree_isEmpty(B))
        return  0;
    else if(covered_by(A,B))
        return 1;
    else
        return contained_by(A,tree_left(B)) || contained_by(A,tree_right(B));
}

tree_t insert_tree(int elt, tree_t tree)
{
    if(tree_isEmpty(tree))
        return tree_make(elt,tree_make(),tree_make());
    else if(elt>=tree_elt(tree))
        return tree_make(tree_elt(tree),tree_left(tree),insert_tree(elt,tree_right(tree)));
    else
        return tree_make(tree_elt(tree),insert_tree(elt,tree_left(tree)),tree_right(tree));
}