### **C++ Syntax Cheatsheet**

#### **1. Variables**
- **Declaration**: `type variable_name;`
- **Initialization**: `type variable_name = value;`

#### **2. Arrays**
- Declare: `type array_name[size];`
- Access: `array_name[index];`

#### **3. Strings**
- Include: `#include <string>`
- Declare: `std::string name;`
- Concatenate: `name += "text";`

#### **4. Structs**
- Define:
  ```cpp
  struct StructName {
      type field_name;
  };
  ```
- Access: `struct_instance.field_name;`

#### **5. Functions**
- Define:
  ```cpp
  return_type function_name(parameters) {
      // Code
      return value; // Optional, if return_type is not void
  }
  ```
- Call: `function_name(arguments);`

#### **6. Loops**
- **For Loop**:
  ```cpp
  for (initialization; condition; increment) {
      // Code
  }
  ```
- **While Loop**:
  ```cpp
  while (condition) {
      // Code
  }
  ```

#### **7. Conditionals**
- **If Statement**:
  ```cpp
  if (condition) {
      // Code
  } else if (another_condition) {
      // Code
  } else {
      // Code
  }
  ```
- **Switch Statement**:
  ```cpp
  switch (variable) {
      case value1:
          // Code
          break;
      case value2:
          // Code
          break;
      default:
          // Code
  }
  ```

#### **8. Input/Output**
- **Input**: `std::cin >> variable;`
- **Output**: `std::cout << "Message";`

#### **9. Pointers**
- Declare: `type* pointer_name;`
- Assign Address: `pointer_name = &variable;`
- Dereference: `*pointer_name;`

#### **10. Classes**
- Define:
  ```cpp
  class ClassName {
  private:
      type field_name;
  public:
      return_type method_name(parameters);
  };
  ```
- Create Object: `ClassName object_name;`

#### **11. Include Libraries**
- Syntax: `#include <library_name>`

#### **12. Namespaces**
- Use Standard Namespace: `using namespace std;`

#### **13. Comments**
- Single Line: `// Comment`
- Multi-Line:
  ```cpp
  /*
  Multi-line
  Comment
  */
  ```

#### **14. Compilation**
- Compile: `g++ filename.cpp -o output_name`
- Run: `./output_name`

#### **15. Error Handling**
- **Try-Catch Block**:
  ```cpp
  try {
      // Code
  } catch (exception_type e) {
      // Handle Error
  }
  ```

