<p align="center">
<img src="doc/OLEX.png" align="center" width="360" height="125"/> 
 </p>

# OLEX
A Very Janky Lexical Analyser

### Tester file
``` 
int i = 0;
float c = 0.0;
boolean b = false;
``` 
### Example
``` c++
#include <tokenizer.h>

int main() {
  olex::tokenizer token;
  token.register_item(olex::lexical_item("operators", 2, "+", "-"));
  token.register_item(olex::lexical_item("assignment", 2, "=", "=:"));
  token.register_item(olex::lexical_item("type", 3, "int", "float", "boolean"));
  token.register_item(olex::lexical_item("seperator", olex::lexical_item::flags::FORCE, 1, ";"));

  token.tokenize_file("tester.txt");
  
  olex::token_item t;
  while (!t.last_item) {
    t = token.get_next_token();
    printf("{\n Token: %s,\n Value: %s,\n Line: %i,\n Word: %i\n}\n", 
      t.token.c_str(), t.value.c_str(), t.line, t.word);
  }

}
```

  
