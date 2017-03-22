 /* bar5.c */
 /* Set x to be am integer as expected by foo5.c 
 * Because x is declared but not instantiated it becomes a weak
 * symbol. Thus, the initialized global variable x from foo5.c
 * will be the strong variable, thus its value will be used
 * here
 */
 int x;

 void f()
 {
 /* Set x to itself so it remains the expected value */
 x = x;
 }
