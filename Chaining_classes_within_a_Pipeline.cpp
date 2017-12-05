/*
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


// Chaining_classes_within_a_Pipeline
// Author : bebenlebricolo
// Date: 04/12/2017 (dd/mm/yyyy)

// Version	|	date	|	comment
//	v 0.1	| 04/12/2017| First tests / release of this test program
//  v 0.2	| 05/12/2017| Small improvements - added modification tracking (Pipeline) and Pipeline object handles bypassing management of elements

// Using a Pipeline to transform a value (input) in a given order.
// Pipeline may point toward certain PipelineElement values (array of them)
// This may be used to chain several functions or classes and process them all at once.

#include "stdafx.h"
#include <iostream>
using namespace std;

// Max size of the array containing all elements pointers
const int max_pipeline_size = 10;

// Pipeline Element class : used to create an array of pipeline elements later
class PipelineElement {
public:
	PipelineElement():value(0),bypass(false){}
	PipelineElement(int a) : value(a),bypass(false){}
	virtual int compute(int a) { return 0; }	// basic function which is masked by each of the derived classes (optional 2nd argument)
	void set_bypass(bool state) 
	{
		if (state != bypass) {
			bypass = state;
			changed = true;
		}
	}
	void clear_changed() { changed = false; }
	bool bypassed() { return bypass; }
	bool has_changed() { return changed; }
protected:
	int value;
	bool bypass;
	bool changed;
};

// Handles additions (Single input class)
class Addition : public PipelineElement {
public:
	Addition():PipelineElement(){}
	Addition(int a):PipelineElement(a){}
	int compute(int a) { 
		if(!bypass) return a + value; 
		else return a;
	}
};

// Handles multiplication
class Multiplication : public PipelineElement {
public:
	Multiplication():PipelineElement() {}
	Multiplication(int a):PipelineElement(a) {}
	int compute(int a) {
		if (!bypass) return a*value;
		else return a;
	}
};

class Modulator : public PipelineElement {
public:
	Modulator() : PipelineElement(){}
	Modulator(int a) :PipelineElement(a) {}
	int compute(int a) {
		if (!bypass) return a % value;
		else return a; 
	} // Modulation via %
};

// Here is the "pipeline" used.
// It simply chains PipelineElements in an array
// And computes the overall result by chaining them.
// If one, or many, of them is deactivated, then this given element will
// be bypassed.
class Pipeline{
public:
	Pipeline() :iterator(0),tot_elements(0),force_calculation(true) {
		init_array();
		init_last_results();
	}

	// First init the array with NULL pointers
	int init_array()
	{
		for (int i = 0; i < max_pipeline_size; i++)
		{
			my_elements[i] = NULL;
		}
		return 0;
	}

	// Initialize the last_result array with zeros by default
	void init_last_results(int16_t init_value = 0) {
		for (int i = 0; i < max_pipeline_size + 1; i++)
		{
			last_values[i] = init_value;
		}
	}

	bool pipeline_has_changed() {
		bool has_changed = false;
		for (int i = 0; i < tot_elements; i++) {
			if (my_elements[i] != NULL && my_elements[i]->has_changed()) {
				has_changed = true;
				my_elements[i]->clear_changed();
			}
		}return has_changed;
	}

	// Function used when removing an element in the Pipeline
	// when removing an element at the i-th position
	// shifts all elements whose position is above i to the previous one
	void left_shift(int position)
	{
		if (position + 1< max_pipeline_size)
		{
			my_elements[position] = my_elements[position + 1];
			left_shift(position + 1);
		}
	}

	// removes one element in the array
	void remove_element(int position) {
		if (position > tot_elements) return;
		if (tot_elements - 1 != 0) left_shift(position);
		my_elements[tot_elements] = NULL;
		tot_elements--;
		iterator--;
	}

	// Adds an element into the Pipeline
	const void add_element(PipelineElement* element)
	{
		if (element == NULL) return; // Discards request if element is NULL
		if (iterator >= max_pipeline_size) return;	// Discards request if array is full
		my_elements[iterator] = element;
		tot_elements++;
		if (iterator + 1 < max_pipeline_size) iterator++; 
		force_calculation = true;
	}

	// Calculates the whole transformation 
	// -> Puts in a sequence all compute methods
	// And computes them in a row (chaining them)
	// Note : bypassing elements is done internally in each element.
	// It might be justified to process this directly inside the Pipeline class instead of within the element
	// -> Saves time and processing power if it is done inside Pipeline (less calls - returns)
	int transform(int input)
	{
		int intermediate = 0;
		if (pipeline_has_changed()) force_calculation = true;
		for (int i = 0; i < max_pipeline_size; i++)
		{
			if (my_elements[i] != NULL)
			{
				if (last_values[i] == input && !force_calculation ) return last_values[tot_elements]; // Compares to the old input value
				else last_values[i] = input;	// stores the new input		
				if (my_elements[i]->bypassed()) intermediate = input;
				else {
					intermediate = my_elements[i]->compute(input);	// stores result in an intermediate value
					input = intermediate; // then next input is the intermediate we've juste calculated
				}
				last_values[i + 1] = intermediate;
			}
			else last_values[i + 1] = 0;
		}
		force_calculation = false;
		return intermediate;
	}

	// Test functions which prints a standard pattern 
	// Prints informations about elements and the array, such as 
	// addresses of elements in the array and their bypass state (Yes or No)
	void print_elements()
	{
		cout << "--------------------------" << endl;
		cout << "printing elements : " << endl;
		cout << "--------------------------" << endl;

		for (int i = 0; i < max_pipeline_size; i++)
		{
			cout << "my_elements[" << i << "] = " << my_elements[i];
			if (my_elements[i] == NULL) cout << endl;
			else
			{
				cout << " -> bypassed : ";
				if (my_elements[i]->bypassed()) cout << "Yes" << endl;
				else cout << "No" << endl;
			}

		}
		cout << "total element number = " << tot_elements << endl;
	}

private:
	PipelineElement* my_elements[max_pipeline_size];
	int last_values[max_pipeline_size + 1];
	int iterator;
	int tot_elements;
	bool force_calculation;
};


int main()
{

	// First creates a few objects and add them in the pipeline
	Addition addition(25);	
	Multiplication multi(2);
	Pipeline pipe;	// Instanciating a Pipeline
	cout << "adding addition element to pipeline" << endl;
	pipe.add_element(&addition);	// Adding addition object to the pipeline
	cout << "pipe.transform(12) = " << pipe.transform(12) << endl;
	pipe.add_element(&multi);		// Adding multi object to the pipeline
	cout << "adding multiplication element to pipeline" << endl;
	cout << "pipe.transform(12) = " << pipe.transform(12) << endl;
	cout << "addition.compute(12) = " << addition.compute(12) << endl;
	cout << "multi.compute(12) = " << multi.compute(12) << endl;

	multi.set_bypass(true);
	pipe.print_elements();
	cout << "pipe.transform(20) = " << pipe.transform(20) << endl;
	cout << "pipe.transform(20) = " << pipe.transform(20) << endl;
	multi.set_bypass(false);
	cout << "pipe.transform(20) = " << pipe.transform(20) << endl;
	cout << "pipe.transform(40) = " << pipe.transform(40) << endl;

	/*
	// instanciating 2 new objects
	Addition barbe(140);
	Multiplication boubi(3);


	pipe.add_element(&barbe);	// adding addition object to the pipeline
	pipe.add_element(&boubi);	// adding multiplication object to the pipeline
	cout << "added addition (barbe (140) ) and multiplication (boubi (3) ) " << endl;
	cout << endl;
	cout << "pipe.transform(12) = " << pipe.transform(12) << endl;
	barbe.set_bypass(true);	// Now inactive	-> will not generate any result
	boubi.set_bypass(true); // Now inactive -> will not generate any result
	pipe.print_elements();
	pipe.remove_element(2);	// Removes the element located at 3rd position
	pipe.print_elements();
	

	Modulator mod(420);
	pipe.add_element(&mod);
	pipe.print_elements();
	cout << "pipe.transform(12) = " << pipe.transform(12) << endl;
	*/
    return 0;
}

