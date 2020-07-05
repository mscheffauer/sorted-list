#pragma once

#include <iostream>
#include <functional>

// sorted_list
template<typename T, typename C = std::less<T>>
class sorted_list
{

	typedef struct GenListNode {

		GenListNode* prev = nullptr;
		GenListNode* next = nullptr;
		T data = 0;
	}GenListNode;

public:

	class iterator {
		friend class sorted_list;
	public:
		using value_type = T;
		using pointer = value_type*;
		using difference_type = std::ptrdiff_t;
		using reference = T&;
		using iterator_category = std::bidirectional_iterator_tag;

		iterator() = default;
		iterator(const iterator&) = default;
		iterator(iterator&&) = default;
		~iterator() = default;
		iterator& operator=(const iterator&) = default;
		iterator& operator=(iterator&&) = default;

		iterator operator+(const difference_type& movement)
		{
			auto temp(*this);
			for (auto i = 0; i < movement; i++)
			{
				temp++;
			}
			return temp; 
		}
		iterator operator-(const difference_type& movement)
		{
			auto temp(*this);
			for (auto i = 0; i < movement; i++)
			{
				temp--;
			}
			return temp;
		}

		bool operator==(const iterator& i) const {
			return m_pos == i.m_pos;
		}

		bool operator!=(const iterator& i) const {
			return !operator==(i);
		}

		iterator& operator++() {
			if (m_pos != nullptr) { m_pos = m_pos->next; } return *this;
		}
		iterator operator++(int) {
			const iterator tmp(*this);
			if (m_pos != nullptr) {
				m_pos = m_pos->next;
			}
			return tmp;
		}

		iterator& operator--() {
			if (m_pos != nullptr) { m_pos = m_pos->prev; } return *this;
	}
		iterator operator--(int) {
			const iterator tmp(*this);
			if (m_pos != nullptr) {
				m_pos = m_pos->prev;
			}
			return tmp;
		}


		T& operator*() const {
			if (m_pos != nullptr)
			{
				return m_pos->data;
			}
		}
	private:
		GenListNode* m_pos{ nullptr };
		explicit iterator(GenListNode* pos) : m_pos(pos) {}
	};
	class reverse_iterator {
		friend class sorted_list;
	public:
		using value_type = T;
		using pointer = value_type*;
		using difference_type = std::ptrdiff_t;
		using reference = T&;
		using iterator_category = std::bidirectional_iterator_tag;

		reverse_iterator() = default;
		reverse_iterator(const reverse_iterator&) = default;
		reverse_iterator(reverse_iterator&&) = default;
		~reverse_iterator() = default;
		reverse_iterator& operator=(const reverse_iterator&) = default;
		reverse_iterator& operator=(reverse_iterator&&) = default;

		reverse_iterator operator+(const difference_type& movement)
		{
			auto temp(*this);
			for (auto i = 0; i < movement; i++)
			{
				temp++;
			}
			return temp;
		}
		reverse_iterator operator-(const difference_type& movement)
		{
			auto temp(*this);
			for (auto i = 0; i < movement; i++)
			{
				temp--;
			}
			return temp;
		}

		bool operator==(const reverse_iterator& i) const {
			return m_pos == i.m_pos;
		}
		bool operator!=(const reverse_iterator& i) const {
			return !operator==(i);
		}
		reverse_iterator& operator++() {
			if (m_pos != nullptr) { m_pos = m_pos->prev; } return *this;
		}
		reverse_iterator operator++(int) {
			const reverse_iterator tmp(*this);
			if (m_pos != nullptr) {
			m_pos = m_pos->prev;
			}
			return tmp;
		}

		reverse_iterator& operator--() { if (m_pos != nullptr) { m_pos = m_pos->next; } return *this; }
		reverse_iterator operator--(int) {
			const reverse_iterator tmp(*this);
			if (m_pos != nullptr) {
				m_pos = m_pos->next;
			}
			return tmp;
		}
		T& operator*() const {
			if (m_pos != nullptr)
			{
				return m_pos->data;
			}
		}
	private:
		GenListNode* m_pos{ nullptr };
		explicit reverse_iterator(GenListNode* pos) : m_pos(pos) {}
	};


private:

	GenListNode* first;
	GenListNode* last;
	int count;

	GenListNode* getNext(GenListNode* curr) const {

		if (curr != nullptr)
		{
			return curr->next;
		}
		return nullptr;
	};

	GenListNode* getPrev(GenListNode* curr) const {

		if (curr != nullptr)
		{
			return curr->prev;
		}
		return nullptr;
	};

	bool eraseSection(const T s, const T e, C co = C()) {

		GenListNode* curr = first;
		GenListNode* start = nullptr;
		GenListNode* end = nullptr;
	
		int c = 0;
		while (curr != nullptr)
		{
			GenListNode* temp = curr;

			curr = getNext(curr);

			if (((co(s,temp->data)) || (temp->data == s) ) && ((co(temp->data,e)) || (temp->data == e)))
			{
				if (c == 0)
				{
					if (temp->prev != nullptr)
					{
						start = temp->prev;
					}
					else {
						start = nullptr;
					}
				}
				c++;
				delete temp;
				count--;
			}
			else if (co(e,temp->data))
			{

				end = temp;
				break;

			}
		}

		if (c > 0)
		{
			if (start == nullptr)
			{
				first = end;
			}
			else {
				start->next = end;
			}
			if (end == nullptr)
			{
				last = start;
			}
			else {
				end->prev = start;

			}
			return true;
		}
		return false;
	};

	int InsertChecker(GenListNode** mN, GenListNode* curr, const T& value, C co = C()) {

		if (curr->data == value) {
			return 3;
		}
		else if (co(curr->data, value)) {
			return 0;
		}
		else if (co(value,curr->data)) {
			auto myNode = new GenListNode;
			myNode->data = value;
			count++;

			if (curr == first)
			{
				first->prev = myNode;
				myNode->next = first;
				first = myNode;
			}
			else {
				myNode->next = curr;
				myNode->prev = curr->prev;
				if (curr->prev != nullptr) {
					curr->prev->next = myNode;
				}
				curr->prev = myNode;
			}
			*mN = myNode;

			return 2;
		}
		return 1;
	};

	// inserts element into list
	std::pair<iterator, bool> insertP(const T& value) {
		GenListNode* curr = first;
		std::pair<iterator, bool> result;
		int broke = 0;
		if (first == nullptr)
		{
			first = new GenListNode;
			first->data = value;
			last = first;
			count++;
			result.first = iterator(first);
			result.second = true;
			return result;
		}

		while (curr != nullptr)
		{
			GenListNode* maNode;
			broke = InsertChecker(&maNode, curr, value);
			if (broke > 1) {
				if (broke == 3)
				{
					result.second = false;
					result.first = iterator(curr);

				}
				else {
					result.second = true;
					result.first = iterator(maNode);

				}
			
				break;
			}
			curr = getNext(curr);
		}
		if (broke <= 1)
		{
			auto myNode = new GenListNode;
			myNode->data = value;
			myNode->prev = last;
			if (last != nullptr) {
				last->next = myNode;
			}
			last = myNode;
			result.first = iterator(last);
			result.second = true;
			count++;
		}
		return result;
	};

	
public:
	
	//constructor, destructor
	sorted_list(GenListNode* first = nullptr, GenListNode* last = nullptr, int count = 0) : first(nullptr), last(nullptr), count(0) {};
	virtual ~sorted_list() { clear(); };

	//copy constructor, assignment operator
	sorted_list( sorted_list& l) : sorted_list(l.first,l.last,l.count)
	{
		iterator it;
		for (it  = l.begin(); it != l.end(); it++)
		{
			insert(*it);
		}
	}
	friend void swap(sorted_list& a, sorted_list& b) noexcept {
		using std::swap;
		//allow finding the best overload
		swap(a.count, b.count);
		swap(a.first, b.first);
		swap(a.last, b.last);

	}
	sorted_list& operator=(sorted_list l) noexcept {
		// NOTE: l is a fresh copy
		// using copy constructor
		
		swap(*this, l);
		return *this;
	} //~l -> deletes our old data



	//normal class functions
	// checks if value is in list
	bool find(const T& value) const
	{
		GenListNode* curr = first;
		while (curr != nullptr)
		{
			if (curr->data == value)
			{
				return true;
				break;
			}
			else {
				curr = getNext(curr);
			}
			
		} 
		return false;
	};


	// removes element and returns true
	// if value was found in list
	bool erase(const T& value) {
		return eraseSection(value, value);
	};

	// returns the number of elements
	size_t size() const { return (size_t)count; };
	// checks if there are any elements
	bool empty() const {
		return (count == 0);
	}; 
	// returns “smallest” element
	T& front() const { 
		if (first != nullptr)
		{
			return first->data;
		}
	
	}; 
	 // returns “greatest” element
	T& back() const {
		if (last != nullptr)
		{
			return last->data;
		}
	
	};
	// removes “smallest” element
	void pop_front() {
		if (first != nullptr)
		{
			erase(first->data);
		}
	
	}; 

	 // removes “greatest” element
	void pop_back() {
		if (last != nullptr)
		{
			erase(last->data);
		}
	};

	// empties list
	void clear() {
		if ((last != nullptr)&& (first != nullptr))
		{
			eraseSection(first->data, last->data);
			first = nullptr;
			last = nullptr;

		}
	
	}; 


	//iterator functions
	// iterator to the beginning of list
	 iterator begin() {
		iterator out = iterator(sorted_list<T,C>::first);
		return out;
	};
	// iterator to the end of list
	 iterator end() {
		iterator out = iterator(sorted_list<T,C>::last);
		return ++out;
	};
	// iterator to the beginning of the reversed list
	 reverse_iterator rbegin() {
		reverse_iterator out = reverse_iterator(sorted_list<T,C>::last);
		return out;
	};
	// iterator to the end of the reversed list
	 reverse_iterator rend() {
		reverse_iterator out = reverse_iterator(sorted_list<T,C>::first);	
		return ++out;
	};

	// insert value, returns a pair consisting of an iterator to the
	// inserted element (or to the element that prevented the insertion)
	// and a bool: true if the insertion took place, false otherwise
	std::pair<iterator, bool> insert(const T& value) {
		return insertP(value);
		 
	};

	// removes all elements in the range [first, last)
	void erase(iterator first, iterator last) {
		iterator mylast = --last;
		eraseSection(*first, *mylast);

	};
	
	// removes all elements satisfying predicate p
	template<class UnaryPredicate> void erase_if(UnaryPredicate p) {
		iterator it;
		
		for (it = begin(); it != end(); it++)
		{
	
			if (p(*(it-1)))
			{
				erase(*(it-1));
			}
			
		}
		if (p(last->data))
		{
			erase(last->data);
		}
		
	}


}; 


