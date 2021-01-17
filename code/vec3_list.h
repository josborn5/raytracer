#ifndef VEC3_LIST_H
#define VEC3_LIST_H

#include "vec3.h"

struct vec3_list_item
{
	vec3 item;
	vec3_list_item* next;
};

class vec3_list
{
	public:
		vec3_list()
		{
			first_node = NULL;
			last_node = NULL;
		}

		void add(vec3 &item)
		{
			vec3_list_item* new_node = new vec3_list_item;
			new_node->item = item;
			new_node->next = NULL;

			if (first_node == NULL)
			{
				first_node = new_node;
				last_node = new_node;
			}
			else
			{
				last_node->next = new_node;
				last_node = new_node;
			}

			++count;
		}

		vec3_list_item* first()
		{
			return first_node;
		}

	private:
		vec3_list_item *first_node;
		vec3_list_item *last_node;
		int count;
};

#endif