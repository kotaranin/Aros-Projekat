## PROJEKAT - SANTA CLAUS PROBLEM

Projekat predstavlja rešenje problema "Santa Claus" iz knjige "The Little Book of Semaphores" koji zadat na sledeći način:

"Santa Claus sleeps in his shop at the North Pole and can only be awakened by either (1) all nine reindeer being back from their vacation in the South Pacific, or (2) some of the elves having difficulty making toys; to allow Santa to get some sleep, the elves can only wake him when three of them have problems. When three elves are having their problems solved, any other elves wishing to visit Santa must wait for those elves to return. If Santa wakes up to find three elves waiting at his shop’s door, along with the last reindeer having come back from the tropics, Santa has decided that the elves can wait until after Christmas, because it is more important to get his sleigh ready. (It is assumed that the reindeer do not want to leave the tropics, and therefore they stay there until the last possible moment.) The last reindeer to arrive must get Santa while the others wait in a warming hut before being harnessed to the sleigh.
Here are some additional specifications:

+ After the ninth reindeer arrives, Santa must invoke _prepareSleigh_, and then all nine reindeer must invoke _getHitched_.
+ After the third elf arrives, Santa must invoke _helpElves_. Concurrently, all three elves should invoke _getHelp_.
+ All three elves must invoke _getHelp_ before any additional elves enter (increment the elf counter).
  
Santa should run in a loop so he can help many sets of elves. We can assume that there are exactly 9 reindeer, but there may be any number of elves."

### POKRETANJE PROGRAMA

Nakon kloniranja ovog repozitorijuma, program se u terminalu pokreće na sledeći način:
1. Najpre je potrebno da se pozicionirate u odgovarajući direktorijum:
   ![image](https://github.com/kotaranin/Aros-Projekat/assets/158298700/d440ba2a-2e07-4df4-97d5-9d75bbd9444e)
2. Pokrenite komandu _make kompajler_:
   ![image](https://github.com/kotaranin/Aros-Projekat/assets/158298700/49f6cc89-de9a-4ade-a883-12a1bbf26430)
3. A potom i komandu _./a.out_:
   ![image](https://github.com/kotaranin/Aros-Projekat/assets/158298700/941b5197-807b-45a8-9cc9-56b22cb2844c)
