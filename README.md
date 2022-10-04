# Basic Math Evaluator

### Contributors:
 - thelonecodist (just me lol)
	 - Github: [DrkWithT](https://github.com/DrkWithT)
	 - Discord: `DerkT#0237`

### References:
 1. The algorithm: [Shunting Yard Algorithm](https://en.wikipedia.org/wiki/Shunting_yard_algorithm)
 2. The evaluator: [Eval RPN](https://www.tutorialspoint.com/evaluate-reverse-polish-notation-in-cplusplus-program)

### Implementation Notes:
 - Precedence:
	 - `x, /`: Higher priority for multiply and divide.
   - `+, -`: Less Priority for add and subtract.
 - Some operations like signs, powers, and bitwise are not supported yet.
 - Also, parentheses are planned.
 - This was originally a project I sprinted in 2 days on `Replit.com`. Note that folders such as `.ccls-cache` may not be needed.

### Usage Notes:
 - If using this project on Replit, you must edit the run command within the `.replit` file.
 - If you see red squiggles on Replit, ignore them. My hand-written Makefile is smart enough. :) 

### Summary: (PLEASE READ!)
This C project is a simple math expression evaluator with token checking. It uses the shunting yard algorithm to convert normal math syntax like `1 + 2 x 3` into _reverse polish notation_ (RPN). In this example, the RPN is `1 2 3 x +`. This syntax orders the numbers and operators in the right order to be evaluated by precedence. Then, the RPN is evalutated into an integer using the algorithm in the _Eval RPN_ link.

Also, keep in mind that since this supports floats, results could be _very_ slightly off. Thus, not all expressions will give an exact result. I will add the exponent operator and parentheses whenever inspiration finds me again.

Finally, I use `goto` for a well-defined purpose: jumping out of a nested loop or if else block to some cleanup code. I know it is disliked, but `goto` does have niche uses.

Feel free to modify my kinda messy code.

### How to use outside of Replit:
 1. Go to Shell.
 2. Enter `make all` to compile my code into an executable.
 3. Enter `./bin/main <expression>` to evaluate some arithmetic expression.
		 - Example: `./bin/main 1.5 + 2.0 x 2.5` gives `6.500000`.
 4. Enter `make clean` to remove the old executable _before_ each rerun. This is good practice!
 5. And rinse and repeat! Have fun ~~debugging if something breaks~~.
