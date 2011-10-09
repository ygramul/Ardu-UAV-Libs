/*
 * Simple "shell" to show and set properties with a terminal
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */
#ifndef Shell_H
#define Shell_H
   
#include <WProgram.h> //It is very important to remember this!

#define MAX_COMMANDLIST_SIZE 25

#define FUNC 1
#define UINT8 2
#define INT8 3
#define UINT16 4
#define INT16 5
#define UINT32 6
#define INT32 7

#define MODE_PARAMETER 1
#define MODE_FUNCTION 2

typedef void (*func_callback_type) ();

typedef union
{
  struct
  {
    func_callback_type callback;
  };
  struct
  {
    uint8_t *uprop8;
  };
  struct
  {
    int8_t *prop8;
  };
  struct
  {
    uint16_t *uprop16;
  };
  struct
  {
    int16_t *prop16;
  };
  struct
  {
    uint32_t *uprop32;
  };
  struct
  {
    int32_t *prop32;
  };
} property_type;

// task list
typedef struct
{
    const char* property_name;
    const char* help_text;
    uint8_t type;
    property_type property;
} command_type;

class Shell {
private:
	char commandLineBuffer[100];
	int commandLinePtr;
	boolean commandLineAvailable;
        boolean writeable;
        uint8_t _mode;
	func_callback_type _active_callback_func;

  	command_type command_list[MAX_COMMANDLIST_SIZE];
        volatile int last_command;

	void parse_set(String _optionstring);
	void parse_show(String _optionstring);
	void parse_help(String _optionstring);
        void call_callback_func(String _optionstring);
        int get_property_index(String _property);
        void list_properties();
	void show_help();
public:
	Shell();
	~Shell();
        // read a complete row and parse it. For example: "set size 10"      
	void parse_command(const char* _commandstring);
	void parse_command(uint8_t incomingByte);

	// add a new command. For example: add_command("size", "to set the size of something", &mysize)
	int  add_command(const char* _property_name, const char* _help, uint8_t* _property);
	int  add_command(const char* _property_name, const char* _help, int8_t* _property);
	int  add_command(const char* _property_name, const char* _help, uint16_t* _property);
	int  add_command(const char* _property_name, const char* _help, int16_t* _property);
	int  add_command(const char* _property_name, const char* _help, uint32_t* _property);
	int  add_command(const char* _property_name, const char* _help, int32_t* _property);
	int  add_command(const char* _property_name, const char* _help, func_callback_type _callback_function);
        void stop_active_function();

        boolean is_writeable();
        void set_readonly();
        void set_readwrite();
};
#endif

