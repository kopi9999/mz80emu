# Modules theory of operation

##  Function

Every **module** is a dynamic library, which contains functions for emulation of single computer component. **Modules** are meant to be loaded at runtime. Before usage component **instances**, and **interfaces** are created. **Instance** variable holds information about current state of a single component, and **interface** variable contains data on components single input, or output. Those variables have to be destroyed before **module** unload.