# gensrc

A CLI preprocessor and code generator for boilerplate code.

## Template Code and Preprocessing

You may write boilerplate code or text constantly. However,
certain content within that boilerplate may vary. Some examples are
Java classes and C header files. This process is consequently
very slow and redundant.

gensrc's preprocessing generates code/text for these scenarios
and inserts any specific defined values so you don't have to
write it constantly.

Param files contain the definitions needed for substituting
varying data. (Similar to Python string variable definitions)

Template files contain the frequently used code with the param file
value names contained in between with special syntax.

gensrc will then go through the template file and replace the aforementioned
syntax with the values defined under the specified name in the param file.
It also progressively writes the results to an output file during all of this.
The text will then be ready for compilation, interpreting, or reading.

Whitespace does not matter in gensrc's syntax for both param and template
files. The syntax for each type of gensrc file and an example of usage can be
found in the proceeding sections.

### Param Files

This is where all the param names and values are defined.
These values will be substituted in the locations where the name
is written when gensrc is preprocessing the template file.

The name is written before an equals sign, followed by the value
in quotations:

`name = "value"`

While whitespace can be used within the param name, it will be
ignored when being read by gensrc. 

### Template Files

Template files contain any code/text you want with the following syntax
for text that varies and may have preset values:

`<* name *>`

The area between the `<**>` characters will be replaced with the value
that was defined under the written name. In this case, it will be replaced
with the text `"value"` since that is what the param `name` was defined with
in the param file.

### Example Param File, Template File, and Output in Java

#### Param File:

```
class_name = "User"
api_url = "https://website.com/api/user"
```

#### Template File:

```
class <* class_name *> {
	private final String URL = "<* api_url *>";
}
```

#### Output:

```
class User {
	private final String URL = "https://website.com/api/user";
}
```
