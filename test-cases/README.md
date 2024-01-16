# Action Items
- [x] registration wihin nested class
    - this can mitigate the need to expose data, but adds complexity of registration code being distributed
    - this will assert (you) have privelages to modify the nested class, which may not be true
- [x] add example for derived class
    - derived + nested may create complex scenario
- [ ] add context of limitation with current workflow (rotor)

# Requirements
- registration code is added for a specified class
    - this imposes the implicit requirement that all data (memory address) must be accessible from the class performing the registration

# Descriptions

## case-0
Data exists as class members of the class performing registration.

**Simplification**
* single structure data
* nested single structure data

**Request**
Inferred from header file `/// \register data`

## case-1
Data exists as base classes of the class performing registration.

**Simplification**
* single structured data
* nested single structure data

**Request**
The class derives from the data so it must be specified:
```
register System::Data
register System::Inputs
```

## case-3
Data to be registered includes a class with private data.

**Requirement:** The class must expose the the data publicly.

Use the `\register` keyword to indicate to the utility what the method registers.

- [ ] one could manually specify the registration method

```
register method SubSystem::_data
```