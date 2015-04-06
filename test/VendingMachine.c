/* 
 * This C program is the result of desugaring
 * the SugarC program VendingMachine.sugc. 
 */
#include <stdio.h>

typedef enum {
               Idle,
               CoinInserted,
               GiveProduct
             } State;
typedef enum {
               InsertCoin,
               Abort,
               Confirm,
               TakeProduct
             } Event;
int coins = 0;
int productsSold = 0;
void enter_Idle()
{
  printf("--------------------------------\n");
  printf("=> Idle\n");
  coins = 0;
  printf("Coins: %d\n", coins);
  printf("--------------------------------\n");
}
void exit_Idle()
{
}
void enter_CoinInserted()
{
  printf("--------------------------------\n");
  printf("=> CoinInserted\n");
  coins++;
  printf("Coins: %d\n", coins);
  printf("--------------------------------\n");
}
void exit_CoinInserted()
{
}
void enter_GiveProduct()
{
  printf("--------------------------------\n");
  printf("=> GiveProduct\n");
  productsSold++;
  coins--;
  printf("Products sold: ... %d\n", productsSold);
  printf("Change: .......... %d coins\n", coins);
  coins = 0;
  printf("--------------------------------\n");
}
void exit_GiveProduct()
{
}
Event readEvent()
{
  Event e = -1;
  while(e < 0 || e > 3)
  {
    printf("Please enter an event: ");
    scanf("%d", &e);
  }
  return e;
}
int main(void)
{
  printf("--------Start simulation--------\n");
  printf("Initial State: Idle\n");
  printf("Events:\n");
  printf("0: InsertCoin\n");
  printf("1: Abort\n");
  printf("2: Confirm\n");
  printf("3: TakeProduct\n");
  printf("--------------------------------\n");
  State state = Idle;
  while(1)
  {
    Event event = readEvent();
    switch(state)
    {
      case Idle:
        switch(event)
        {
          case InsertCoin:
            {
              exit_Idle();
              state = CoinInserted;
              enter_CoinInserted();
            }
          break;
          case Abort:
            {
              exit_Idle();
              state = Idle;
              enter_Idle();
            }
          break;
          default:
            break;
        }
      break;
      case CoinInserted:
        switch(event)
        {
          case Confirm:
            {
              exit_CoinInserted();
              state = GiveProduct;
              enter_GiveProduct();
            }
          break;
          case InsertCoin:
            {
              exit_CoinInserted();
              state = CoinInserted;
              enter_CoinInserted();
            }
          break;
          case Abort:
            {
              exit_CoinInserted();
              state = Idle;
              enter_Idle();
            }
          break;
          default:
            break;
        }
      break;
      case GiveProduct:
        switch(event)
        {
          case TakeProduct:
            {
              exit_GiveProduct();
              state = Idle;
              enter_Idle();
            }
          break;
          default:
            break;
        }
      break;
    }
  }
}