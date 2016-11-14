/*
    Programmer: Raymond Muller
    This module generates profile characteristics.
*/

#include <cstdlib>
#include <string>
#include <time.h>

/*
THE MATH:
-Complete generation:
Number of unique people total: 732,058,145,280.  That's about 100x greater than the population of the world.
Number of unique people, per race and gender: 96,909,120
With 300 first and last names combined, 2 at a time, we have only 89,700 unique names per race and gender, meaning at least 1080 people have the exact same name, for each race and gender.
-Incomplete/Realistic generation:
This would generate a population of 318,000,000 unique people, emulating the population of the United States.
Number of people, per race and per gender: 19,875,000
This wrap would produce only 221 same-named people, per race and gender, and therefore 3,536 same named people total, which is well within realistic range (there are over 26,000 people named John Jones alone).
Slapping on a random middle inital, we get 5,721,300 possible names, and only 3 people will have the same name per race and gender, totalling to 48 people with the same name, which is a slightly unrealistic name level.  I will leave out the middle initial for the purposes of this assignment.
However, this would require a "matching system," where we find a person with the highest percent match, perhaps within the 3 hidden levels.
*/

//200 most popular boy's and girl's names for 2016.
//Source: Babycenter.
//Last names are taken by popularity from Mongobay, which in turn takes its data from the US Census.

const int FNAME_NUM = 200;
const int LNAME_NUM = 100; //Per race.

string boyFirstNames[FNAME_NUM] = {"Liam", "Noah", "Ethan", "Mason", "Lucas", "Logan", "Oliver", "Jackson", "Aiden", "Jacob", "Elijah", "James", "Benjamin", "Alexander", "Jack", "Luke", "William", "Carter", "Michael", "Daniel", "Owen", "Gabriel", "Henry", "Matthew", "Wyatt", "Jayden", "Nathan", "Isaac", "Ryan", "Caleb", "Sebastian", "David", "Andrew", "Dylan", "Samuel", "Connor", "Joshua", "Eli", "Hunter", "Jaxon", "Nicolas", "Angel", "Avery", "Bradley", "Miguel", "Giovanni", "Dean", "Kevin", "Eric", "Omar", "Preston", "A.J.", "Antonio", "Ali", "Elliott", "Diego", "Sean", "Ezekiel", "Justin", "Grant", "Ivan", "Matteo", "Brady", "Lorenzo", "Axel", "Joel", "Elliot", "Maverick", "Arthur", "Juan", "Jose", "Enzo", "Rowan", "Beau", "Cayden", "Luis", "Zane", "Tucker", "Jaden", "Jasper", "Grayson", "Levi", "Landon", "Anthony", "Joseph", "Julian", "Max", "John", "Adam", "Christian", "Cameron", "Gavin", "Leo", "Lincoln", "Isaiah", "Evan", "Nolan", "Muhammad", "Hudson", "Dominic", "Thomas", "Brayden", "Christopher", "Colton", "Aaron", "Parker", "Austin", "Nicholas", "Adrian", "Charlie", "Josiah", "Tyler", "Cooper", "Jonathan", "Asher", "Jordan", "Chase", "Jace", "Jeremiah", "Jaxson", "Alex", "Ian", "Easton", "Zachary", "Ezra", "Carson", "Xavier", "Miles", "Blake", "Declan", "Ayden", "Tristan", "Cole", "Nathaniel", "Micah", "Ryder", "Jason", "Harrison", "Sawyer", "Mateo", "Brody", "Greyson", "Camden", "Roman", "Elias", "Luca", "Kai", "Kayden", "Bentley", "Vincent", "Robert", "Bryce", "Jude", "Brandon", "Emmett", "Everett", "Jake", "Jonah", "Wesley", "Finn", "Weston", "Silas", "Ben", "Jameson", "Santiago", "Leonardo", "Bennett", "George", "Damian", "Theodore", "Charles", "Kaiden", "Maddox", "Sam", "Theo", "Xander", "Brantley", "Hayden", "Jax", "Rileyå", "Aidan", "Maxwell", "Jayce", "Marcus", "Graham", "Abel", "Colin", "Kingston", "Ashton", "Braxton", "Caden", "Calvin", "Ryker", "Bryson", "Kyle", "Kaleb", "King", "Kaden", "Malachi", "Patrick"};  //200 Male first names

string girlFirstNames[FNAME_NUM] = {"Emma", "Olivia", "Sophia", "Ava", "Mia", "Isabella", "Charlotte", "Amelia", "Harper", "Emily", "Madison", "Abigail", "Avery", "Lily", "Ella", "Sofia", "Chloe", "Evelyn", "Aria", "Scarlett", "Aubrey", "Ellie", "Zoey", "Zoe", "Elizabeth", "Hannah", "Grace", "Addison", "Audrey", "Riley", "Mila", "Layla", "Nora", "Victoria", "Natalie", "Lucy", "Penelope", "Lillian", "Brooklyn", "Savannah", "Claire", "Anna", "Violet", "Leah", "Stella", "Maya", "Skylar", "Alice", "Maria", "Samantha", "Sarah", "Eva", "Sadie", "Sophie", "Madelyn", "Kennedy", "Hazel", "Hailey", "Julia", "Gabriella", "Aaliyah", "Mackenzie", "Paisley", "Bella", "Caroline", "Eleanor", "Peyton", "Kylie", "Ariana", "Clara", "Piper", "Arianna", "Cora", "Kaylee", "Taylor", "Autumn", "Isabelle", "Camila", "Quinn", "Annabelle", "Alyssa", "Aurora", "Emilia", "Alexa", "Lydia", "Isla", "Naomi", "Ruby", "Valentina", "Allison", "Elena", "Alexis", "Gianna", "Luna", "Madeline", "Eliana", "Aubree", "Hadley", "Lilly", "Sydney", "Reagan", "Bailey", "Vivian", "Serenity", "Faith", "Rylee", "Nevaeh", "Kayla", "Willow", "Ivy", "Brielle", "Isabel", "Kinsley", "Sara", "Molly", "Alexandra", "Morgan", "London", "Liliana", "Lyla", "Jade", "Everly", "Adalyn", "Delilah", "Paige", "Lauren", "Brooke", "Natalia", "Emery", "Jasmine", "Ana", "Khloe", "Gracie", "Kate", "Melody", "Adeline", "Arya", "Jordyn", "Norah", "Melanie", "Eden", "Charlie", "Adalynn", "Athena", "Abby", "Maggie", "Laila", "Mya", "Elise", "Reese", "Jocelyn", "Sienna", "Eliza", "Rose", "Katherine", "Josephine", "Brianna", "Makayla", "Lola", "Mary", "Kendall", "Nur", "Andrea", "Payton", "Ariel", "Mckenzie", "Alaina", "Callie", "Gabrielle", "Juliana", "Emerson", "Lila", "Hayden", "Nicole", "Adelyn", "Trinity", "Cecilia", "Genesis", "Alana", "Evie", "Alina", "Arabella", "Leilani", "Genevieve", "Tessa", "Laura", "Lucia", "Nina", "Presley", "Keira", "Alexandria", "Summer", "Fiona", "Teagan", "Iris", "Parker", "Leila", "Juliette", "Kaitlyn", "Marley"};  //200 female first names. 

//Have last names correspond to race, as determined by the database.
string caucasianLastNames[LNAME_NUM] = {"Smith", "Johnson", "Miller", "Brown", "Jones", "Williams", "Davis", "Anderson", "Wilson", "Martin", "Taylor", "Moore", "Thompson", "White", "Clark", "Thomas", "Hall", "Baker" "Nelson", "Allen", "Young", "Harris", "King","Adams", "Lewis", "Walker", "Wright", "Roberts", "Campbell", "Jackson", "Phillips", "Hill", "Scott", "Robinson", "Murphy", "Cook", "Green", "Lee", "Evans", "Peterson", "Morris", "Collins", "Mitchell", "Parker", "Rogers", "Stewart", "Turner", "Wood", "Carter", "Morgan", "Cox", "Kelley", "Edwards", "Bailey", "Ward", "Reed", "Myers", "Sullivan", "Cooper", "Bennet", "Hughes", "Long", "Fisher", "Price", "Russel", "Howard", "Gray", "Bell", "Watson", "Reynolds", "Foster", "Ross", "Olson", "Richardson", "Snyder", "Powell", "Stevens", "Brooks", "Perry", "West", "Cole", "Wagner", "Meyer", "Kennedy", "Barnes", "Hamilton", "Graham", "Schmidt", "Sanders", "McDonald", "Patterson", "Murray", "Gibson", "Wallace", "Butler", "Hayes", "Burns", "Ellis", "Fox", "Stone"} //100
//For the purpose of time, African-Americans and africans will share the Native American last names, since they overlap anyway.

string hispanicLastNames[LNAME_NUM] = {"Garcia", "Rodriguez", "Martinez", "Hernandez", "Lopez", "Gonzalez", "Perez", "Sanchez", "Ramirez", "Torres", "Flores", "Rivera", "Gomez", "Diaz", "Reyes", "Morales", "Cruz", "Ortiz", "Gutierrez", "Chavez", "Ramos", "Gonzales", "Ruiz", "Alvarez", "Mendoza", "Vasquez", "Castillo", "Jimenez", "Moreno", "Romero", "Herrera", "Medina","Aguilar", "Garza", "Castro", "Vargas", "Fernandez", "Guzman", "Munoz", "Mendez", "Salazar", "Soto", "Delgado", "Pena", "Rios", "Alvarado", "Sandoval", "Contreras", "Valdez", "Guerro", "Ortega", "Estrada", "Nunez", "Maldonado", "Vega", "Vazquez", "Santiago", "Dominguez", "Espinoza", "Silva", "Padilla", "Marquez", "Cortez", "Rojas", "Acosta", "Figueroa", "Luna", "Juarez", "Navarro", "Campos", "Molina", "Avila", "Ayala", "Mejia", "Carillo", "Duran", "Santos", "Salinas", "Robles", "Solis", "Lara", "Cervantes", "Aguirre", "DeLeon", "Ochoa", "Miranda", "Cardenas", "Trujillo", "Velasquez", "Fuentes", "Cabrera", "Leon", "Rivas", "Montoya", "Calderon", "Colon", "Serrano", "Gallegos", "Rosales", "Castenada"}; //100

string nativeLastNames[LNAME_NUM] = {"Smith",
"Johnson",
"Begay",
"Yazzie",
"Locklear",
"Jones",
"Williams",
"Brown",
"Davis",
"Wilson",
"Thompson",
"Thomas",
"Miller",
"Jackson",
"White",
"Martin",
"Lee",
"Hunt",
"James",
"Lewis",
"Taylor",
"Anderson",
"Clark",
"Garcia",
"Martinez",
"Benally",
"Scott",
"Tsosie",
"Moore",
"Nelson",
"King",
"Jacobs",
"Oxendine",
"Walker",
"Nez",
"Harris",
"Allen",
"Hill",
"Mitchell",
"Phillips",
"John",
"Baker",
"Young",
"Adams",
"Chaviz",
"Morgan",
"Roberts",
"Hall",
"Lopez",
"Wright",
"Joe",
"Morris",
"Henry",
"Parker",
"Long",
"Reed",
"George",
"Richardson",
"Carter",
"Robinson",
"Cook",
"Green",
"Campbell",
"Chee",
"Collins",
"Bell",
"Edwards",
"Harrison",
"Evans",
"Stewart",
"Jim",
"Rogers",
"Stevens",
"Charley",
"Sanchez",
"Russell",
"Chavez",
"Bennet",
"Ward",
"Sandoval",
"Howard",
"Cooper",
"Wood",
"Black",
"Gray",
"Ross",
"Murphy",
"Watson",
"Rodriguez",
"Peterson",
"Sam",
"Hernandez",
"Foster",
"Curley",
"Turner",
"Sanders",
"Lowery",
"Brooks",
"Peters",
"Spencer"
                                    }
