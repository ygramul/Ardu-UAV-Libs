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
#include "Shell.h" //include the declaration for this class
       
Shell::Shell(){
  last_command = 0;
  commandLinePtr = 0;
  commandLineAvailable = false;
  writeable = true;
  _mode = MODE_PARAMETER;
  _active_callback_func = 0;
}
       
//<<destructor>>
Shell::~Shell(){/*nothing to destruct*/}
       
// read a complete row and parse it. For example: "set size 10"      
void Shell::parseCommand(const char* _commandstring) {
  String commandStr = _commandstring;
  String command;
  String options;
  if (commandStr.indexOf(" ") > 0) {
    command = commandStr.substring(0, commandStr.indexOf(" "));
    options = commandStr.substring(commandStr.indexOf(" ")+1);
  } else {
    command = _commandstring;
  }
  if (command.equalsIgnoreCase("show")) {
    parseShow(options);
  } else if (command.equalsIgnoreCase("help")) {
    if (options.length() < 1) {
      showHelp();
    } else {
      parseHelp(options);
    }
  } else if (command.equalsIgnoreCase("set")) {
    parseSet(options);
  } else if (command.equalsIgnoreCase("list")) {
    listProperties();
  } else if (command.equalsIgnoreCase("call")) {
    callCallbackFunc(options);
  } else {
    showHelp();
  }
}

void Shell::showHelp() {
    Serial.println("Available commands:");
    Serial.println("set <property> <value>");
    Serial.println("show <property>");
    Serial.println("help <property>");
    Serial.println("call <function>");
    Serial.println("list");
}

void Shell::listProperties() {
  Serial.println("Available properties:");
  for (int i=0; i < last_command; i++) {
    command_type *single_command = &command_list[i];
    const char* property = single_command->property_name;
    Serial.print(property);
    Serial.print(" ");
     if (single_command->type == UINT8) {
        uint8_t *value = single_command->property.uprop8;
        Serial.println(*value, DEC);
     } else
     if (single_command->type == INT8) {
        int8_t *value = single_command->property.prop8;
        Serial.println(*value, DEC);
     } else
     if (single_command->type == UINT16) {
        uint16_t *value = single_command->property.uprop16;
        Serial.println(*value, DEC);
     } else
     if (single_command->type == INT16) {
        int16_t *value = single_command->property.prop16;
        Serial.println(*value, DEC);
     } else
     if (single_command->type == UINT32) {
        uint32_t *value = single_command->property.uprop32;
        Serial.println(*value, DEC);
     } else
     if (single_command->type == INT32) {
        int32_t *value = single_command->property.prop32;
        Serial.println(*value, DEC);
     } else
     if (single_command->type == FUNC) {
        Serial.println(" - function");
     }
  }
}

void Shell::parseSet(String _optionstring) {
  String optionstring = _optionstring;
  String property;
  String value;
  int whitespaceIndex = optionstring.indexOf(" ");
  if (writeable == false) {
    Serial.println("properties are not writeable!");
  } else if (whitespaceIndex > 0) {
    property = optionstring.substring(0, whitespaceIndex);
    value = optionstring.substring(whitespaceIndex+1);
    char str_value[20]; 
    value.toCharArray(str_value, 20);
    int index = getPropertyIndex(property); 
    if (index > -1) {
      command_type *single_command = &command_list[index];
      uint8_t type = single_command->type;
      if (type == UINT8) {
        uint8_t parsed_int = atoi(str_value);
        *(single_command->property.uprop8) = parsed_int;
      } else
      if (type == INT8) {
        int8_t parsed_int = atoi(str_value);
        *(single_command->property.prop8) = parsed_int;
      } else
      if (type == UINT16) {
        uint16_t parsed_int = atoi(str_value);
        *(single_command->property.uprop16) = parsed_int;
      } else
      if (type == INT16) {
        int16_t parsed_int = atoi(str_value);
        *(single_command->property.prop16) = parsed_int;
      } else
      if (type == UINT32) {
        uint32_t parsed_int = atoi(str_value);
        *(single_command->property.uprop32) = parsed_int;
      } else 
      if (type == INT32) {
        int32_t parsed_int = atoi(str_value);
        *(single_command->property.prop32) = parsed_int;
      }
    } else {
      Serial.print("could not find property: ");
      Serial.println(property);
    }
  }
}

void Shell::parseShow(String _optionstring) {
   int index = getPropertyIndex(_optionstring); 
   if (index > -1) {
     command_type *single_command = &command_list[index];
     Serial.print(single_command->property_name);
     Serial.print("=");
     if (single_command->type == UINT8) {
        uint8_t *value = single_command->property.uprop8;
        Serial.print(*value, DEC);
     } else
     if (single_command->type == INT8) {
        int8_t *value = single_command->property.prop8;
        Serial.print(*value, DEC);
     } else
     if (single_command->type == UINT16) {
        uint16_t *value = single_command->property.uprop16;
        Serial.print(*value, DEC);
     } else
     if (single_command->type == INT16) {
        int16_t *value = single_command->property.prop16;
        Serial.print(*value, DEC);
     } else
     if (single_command->type == UINT32) {
        uint32_t *value = single_command->property.uprop32;
        Serial.print(*value, DEC);
     } else
     if (single_command->type == INT32) {
        int32_t *value = single_command->property.prop32;
        Serial.print(*value, DEC);
     }
     Serial.print('\t');
     Serial.println(single_command->help_text);
   } else {
     Serial.print("could not find property: ");
     Serial.println(_optionstring);
   }
}

void Shell::callCallbackFunc(String _optionstring) {
   int index = getPropertyIndex(_optionstring); 
   if (index > -1) {
     command_type *single_command = &command_list[index];
     if (single_command->type == FUNC) {
        _active_callback_func = single_command->property.callback;
     }
     _mode = MODE_FUNCTION;
     _active_callback_func();
   } else {
     Serial.print("could not find function: ");
     Serial.println(_optionstring);
   }
}


void Shell::parseHelp(String _optionstring) {
   int index = getPropertyIndex(_optionstring); 
   if (index > -1) {
     command_type *single_command = &command_list[index];
     Serial.println(single_command->help_text);
   } else {
     Serial.print("could not find property: ");
     Serial.println(_optionstring);
   }
}

void Shell::parseCommand(uint8_t incomingByte) {
  if (_mode == MODE_FUNCTION) {
    if ((incomingByte==7) || (incomingByte==13) || (incomingByte==10)) {
      stopActiveFunction();
    } else {
      _active_callback_func();
    }
  } else {
    if ((incomingByte!=13) && (incomingByte!=10) && (incomingByte!=0)) {
      commandLineBuffer[commandLinePtr] = (unsigned char)incomingByte;
      commandLinePtr++;
      commandLineBuffer[commandLinePtr] = 0;
    }
    if (commandLinePtr >= 100) {
        commandLinePtr = 0;
        incomingByte = 0;
    }
    if ((incomingByte==13) || (incomingByte==10)) {    
      parseCommand(commandLineBuffer);
      commandLinePtr = 0;
    }
  }
}

int Shell::getPropertyIndex(String _property) {
  int index = -1;
  if (_property.length() > 0) {
    for (int i=0; i < last_command; i++) {
      command_type *single_command = &command_list[i];
      String property_name = single_command->property_name;
      if (property_name.equals(_property)) {
         index = i;
         i = last_command;
      }
    }
  }
  return index;
}

// add a new command. For example: add_command("size", "to set the size of something", &mysize)
int Shell::addCommand(const char* _property_name, const char* _help, uint8_t* _property) {
  if (last_command < MAX_COMMANDLIST_SIZE) {
    command_type *single_command = &command_list[last_command];
    single_command->property_name   = _property_name;
    single_command->help_text = _help;
    single_command->type = UINT8;
    single_command->property.uprop8 = _property;
    last_command++;
  }
}

int Shell::addCommand(const char* _property_name, const char* _help, int8_t* _property) {
  if (last_command < MAX_COMMANDLIST_SIZE) {
    command_type *single_command = &command_list[last_command];
    single_command->property_name   = _property_name;
    single_command->help_text = _help;
    single_command->type = INT8;
    single_command->property.prop8 = _property;
    last_command++;
  }
}

int Shell::addCommand(const char* _property_name, const char* _help, uint16_t* _property) {
  if (last_command < MAX_COMMANDLIST_SIZE) {
    command_type *single_command = &command_list[last_command];
    single_command->property_name   = _property_name;
    single_command->help_text = _help;
    single_command->type = UINT16;
    single_command->property.uprop16 = _property;
    last_command++;
  }
}

int Shell::addCommand(const char* _property_name, const char* _help, int16_t* _property) {
  if (last_command < MAX_COMMANDLIST_SIZE) {
    command_type *single_command = &command_list[last_command];
    single_command->property_name   = _property_name;
    single_command->help_text = _help;
    single_command->type = INT16;
    single_command->property.prop16 = _property;
    last_command++;
  }
}

int Shell::addCommand(const char* _property_name, const char* _help, uint32_t* _property) {
  if (last_command < MAX_COMMANDLIST_SIZE) {
    command_type *single_command = &command_list[last_command];
    single_command->property_name   = _property_name;
    single_command->help_text = _help;
    single_command->type = UINT32;
    single_command->property.uprop32 = _property;
    last_command++;
  }
}

int Shell::addCommand(const char* _property_name, const char* _help, int32_t* _property) {
  if (last_command < MAX_COMMANDLIST_SIZE) {
    command_type *single_command = &command_list[last_command];
    single_command->property_name   = _property_name;
    single_command->help_text = _help;
    single_command->type = INT32;
    single_command->property.prop32 = _property;
    last_command++;
  }
}

int Shell::addCommand(const char* _property_name, const char* _help, func_callback_type _callback_function) {
  if (last_command < MAX_COMMANDLIST_SIZE) {
    command_type *single_command = &command_list[last_command];
    single_command->property_name   = _property_name;
    single_command->help_text = _help;
    single_command->type = FUNC;
    single_command->property.callback = _callback_function;
    last_command++;
  }
}

boolean Shell::isWriteable() {
  return writeable;
}

void Shell::setReadonly() {
  writeable = false;
}

void Shell::setReadwrite() {
  writeable = true;
}

void Shell::stopActiveFunction() {
  _mode = MODE_PARAMETER;
  _active_callback_func = 0;
}

