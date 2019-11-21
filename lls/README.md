# Linear Least Squares Algorithm

Implementation of polynomial linear least squares fitting as outlined in chapter 1 of `Data analysis recipes: Fitting a model to data` (https://arxiv.org/pdf/1008.4686.pdf).

## How to use it
 
Compile the project using `make` (and the file `makefile`) then you can run the programm like

```
./polyfitter FILENAME
```

e.g.

```
./polyfitter data.txt
```

where the supplied file should contain three columns (x, y, uncertainties in y), use spaces (not commas or anything else) between the columns.