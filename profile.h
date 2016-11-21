/*
    Programmer: Raymond Muller
    Part of the Profiler project.
    This module generates profile characteristics.
*/

#include <cstdlib>
#include <string>
#include <time.h>

using namespace std;
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
However, this approach would require a "matching system," where we find a person with the highest percent match, perhaps within the 3 hidden levels.
*/

//200 most popular boy's and girl's names for 2016.
//Source: Babycenter.
//Last names are taken by popularity from Mongobay, which in turn takes its data from the US Census.

const int FNAME_NUM = 200;
const int LNAME_NUM = 100; //Per race.
const int OCCUPATION_NUM = 479; // Number of unique occupations.
const int FACT_NUM = 102;

string boyFirstNames[FNAME_NUM] = {"Liam", "Noah", "Ethan", "Mason", "Lucas", "Logan", "Oliver", "Jackson", "Aiden", "Jacob", "Elijah", "James", "Benjamin", "Alexander", "Jack", "Luke", "William", "Carter", "Michael", "Daniel", "Owen", "Gabriel", "Henry", "Matthew", "Wyatt", "Jayden", "Nathan", "Isaac", "Ryan", "Caleb", "Sebastian", "David", "Andrew", "Dylan", "Samuel", "Connor", "Joshua", "Eli", "Hunter", "Jaxon", "Nicolas", "Angel", "Avery", "Bradley", "Miguel", "Giovanni", "Dean", "Kevin", "Eric", "Omar", "Preston", "A.J.", "Antonio", "Ali", "Elliott", "Diego", "Sean", "Ezekiel", "Justin", "Grant", "Ivan", "Matteo", "Brady", "Lorenzo", "Axel", "Joel", "Elliot", "Maverick", "Arthur", "Juan", "Jose", "Enzo", "Rowan", "Beau", "Cayden", "Luis", "Zane", "Tucker", "Jaden", "Jasper", "Grayson", "Levi", "Landon", "Anthony", "Joseph", "Julian", "Max", "John", "Adam", "Christian", "Cameron", "Gavin", "Leo", "Lincoln", "Isaiah", "Evan", "Nolan", "Muhammad", "Hudson", "Dominic", "Thomas", "Brayden", "Christopher", "Colton", "Aaron", "Parker", "Austin", "Nicholas", "Adrian", "Charlie", "Josiah", "Tyler", "Cooper", "Jonathan", "Asher", "Jordan", "Chase", "Jace", "Jeremiah", "Jaxson", "Alex", "Ian", "Easton", "Zachary", "Ezra", "Carson", "Xavier", "Miles", "Blake", "Declan", "Ayden", "Tristan", "Cole", "Nathaniel", "Micah", "Ryder", "Jason", "Harrison", "Sawyer", "Mateo", "Brody", "Greyson", "Camden", "Roman", "Elias", "Luca", "Kai", "Kayden", "Bentley", "Vincent", "Robert", "Bryce", "Jude", "Brandon", "Emmett", "Everett", "Jake", "Jonah", "Wesley", "Finn", "Weston", "Silas", "Ben", "Jameson", "Santiago", "Leonardo", "Bennett", "George", "Damian", "Theodore", "Charles", "Kaiden", "Maddox", "Sam", "Theo", "Xander", "Brantley", "Hayden", "Jax", "Rileyå", "Aidan", "Maxwell", "Jayce", "Marcus", "Graham", "Abel", "Colin", "Kingston", "Ashton", "Braxton", "Caden", "Calvin", "Ryker", "Bryson", "Kyle", "Kaleb", "King", "Kaden", "Malachi", "Patrick"};  //200 Male first names

string girlFirstNames[FNAME_NUM] = {"Emma", "Olivia", "Sophia", "Ava", "Mia", "Isabella", "Charlotte", "Amelia", "Harper", "Emily", "Madison", "Abigail", "Avery", "Lily", "Ella", "Sofia", "Chloe", "Evelyn", "Aria", "Scarlett", "Aubrey", "Ellie", "Zoey", "Zoe", "Elizabeth", "Hannah", "Grace", "Addison", "Audrey", "Riley", "Mila", "Layla", "Nora", "Victoria", "Natalie", "Lucy", "Penelope", "Lillian", "Brooklyn", "Savannah", "Claire", "Anna", "Violet", "Leah", "Stella", "Maya", "Skylar", "Alice", "Maria", "Samantha", "Sarah", "Eva", "Sadie", "Sophie", "Madelyn", "Kennedy", "Hazel", "Hailey", "Julia", "Gabriella", "Aaliyah", "Mackenzie", "Paisley", "Bella", "Caroline", "Eleanor", "Peyton", "Kylie", "Ariana", "Clara", "Piper", "Arianna", "Cora", "Kaylee", "Taylor", "Autumn", "Isabelle", "Camila", "Quinn", "Annabelle", "Alyssa", "Aurora", "Emilia", "Alexa", "Lydia", "Isla", "Naomi", "Ruby", "Valentina", "Allison", "Elena", "Alexis", "Gianna", "Luna", "Madeline", "Eliana", "Aubree", "Hadley", "Lilly", "Sydney", "Reagan", "Bailey", "Vivian", "Serenity", "Faith", "Rylee", "Nevaeh", "Kayla", "Willow", "Ivy", "Brielle", "Isabel", "Kinsley", "Sara", "Molly", "Alexandra", "Morgan", "London", "Liliana", "Lyla", "Jade", "Everly", "Adalyn", "Delilah", "Paige", "Lauren", "Brooke", "Natalia", "Emery", "Jasmine", "Ana", "Khloe", "Gracie", "Kate", "Melody", "Adeline", "Arya", "Jordyn", "Norah", "Melanie", "Eden", "Charlie", "Adalynn", "Athena", "Abby", "Maggie", "Laila", "Mya", "Elise", "Reese", "Jocelyn", "Sienna", "Eliza", "Rose", "Katherine", "Josephine", "Brianna", "Makayla", "Lola", "Mary", "Kendall", "Nur", "Andrea", "Payton", "Ariel", "Mckenzie", "Alaina", "Callie", "Gabrielle", "Juliana", "Emerson", "Lila", "Hayden", "Nicole", "Adelyn", "Trinity", "Cecilia", "Genesis", "Alana", "Evie", "Alina", "Arabella", "Leilani", "Genevieve", "Tessa", "Laura", "Lucia", "Nina", "Presley", "Keira", "Alexandria", "Summer", "Fiona", "Teagan", "Iris", "Parker", "Leila", "Juliette", "Kaitlyn", "Marley"};  //200 female first names. 

//Have last names correspond to race, as determined by the database.
string caucasianLastNames[LNAME_NUM] = {"Smith", "Johnson", "Miller", "Brown", "Jones", "Williams", "Davis", "Anderson", "Wilson", "Martin", "Taylor", "Moore", "Thompson", "White", "Clark", "Thomas", "Hall", "Baker" "Nelson", "Allen", "Young", "Harris", "King","Adams", "Lewis", "Walker", "Wright", "Roberts", "Campbell", "Jackson", "Phillips", "Hill", "Scott", "Robinson", "Murphy", "Cook", "Green", "Lee", "Evans", "Peterson", "Morris", "Collins", "Mitchell", "Parker", "Rogers", "Stewart", "Turner", "Wood", "Carter", "Morgan", "Cox", "Kelley", "Edwards", "Bailey", "Ward", "Reed", "Myers", "Sullivan", "Cooper", "Bennet", "Hughes", "Long", "Fisher", "Price", "Russel", "Howard", "Gray", "Bell", "Watson", "Reynolds", "Foster", "Ross", "Olson", "Richardson", "Snyder", "Powell", "Stevens", "Brooks", "Perry", "West", "Cole", "Wagner", "Meyer", "Kennedy", "Barnes", "Hamilton", "Graham", "Schmidt", "Sanders", "McDonald", "Patterson", "Murray", "Gibson", "Wallace", "Butler", "Hayes", "Burns", "Ellis", "Fox", "Stone"}; //100

string hispanicLastNames[LNAME_NUM] = {"Garcia", "Rodriguez", "Martinez", "Hernandez", "Lopez", "Gonzalez", "Perez", "Sanchez", "Ramirez", "Torres", "Flores", "Rivera", "Gomez", "Diaz", "Reyes", "Morales", "Cruz", "Ortiz", "Gutierrez", "Chavez", "Ramos", "Gonzales", "Ruiz", "Alvarez", "Mendoza", "Vasquez", "Castillo", "Jimenez", "Moreno", "Romero", "Herrera", "Medina","Aguilar", "Garza", "Castro", "Vargas", "Fernandez", "Guzman", "Munoz", "Mendez", "Salazar", "Soto", "Delgado", "Pena", "Rios", "Alvarado", "Sandoval", "Contreras", "Valdez", "Guerro", "Ortega", "Estrada", "Nunez", "Maldonado", "Vega", "Vazquez", "Santiago", "Dominguez", "Espinoza", "Silva", "Padilla", "Marquez", "Cortez", "Rojas", "Acosta", "Figueroa", "Luna", "Juarez", "Navarro", "Campos", "Molina", "Avila", "Ayala", "Mejia", "Carillo", "Duran", "Santos", "Salinas", "Robles", "Solis", "Lara", "Cervantes", "Aguirre", "DeLeon", "Ochoa", "Miranda", "Cardenas", "Trujillo", "Velasquez", "Fuentes", "Cabrera", "Leon", "Rivas", "Montoya", "Calderon", "Colon", "Serrano", "Gallegos", "Rosales", "Castenada"}; //100

string nativeLastNames[LNAME_NUM] = {"Smith", "Johnson", "Begay", "Yazzie", "Locklear", "Jones", "Williams", "Brown", "Davis", "Wilson", "Thompson", "Thomas", "Miller", "Jackson", "White", "Martin", "Lee", "Hunt", "James", "Lewis", "Taylor", "Anderson", "Clark", "Garcia", "Martinez", "Benally", "Scott", "Tsosie", "Moore", "Nelson", "King", "Jacobs", "Oxendine", "Walker", "Nez", "Harris", "Allen", "Hill", "Mitchell", "Phillips", "John", "Baker", "Young", "Adams", "Chaviz", "Morgan", "Roberts", "Hall", "Lopez", "Wright", "Joe", "Morris", "Henry", "Parker", "Long", "Reed", "George", "Richardson", "Carter", "Robinson", "Cook", "Green", "Campbell", "Chee", "Collins", "Bell", "Edwards", "Harrison", "Evans", "Stewart", "Jim", "Rogers", "Stevens", "Charley", "Sanchez", "Russell", "Chavez", "Bennet", "Ward", "Sandoval", "Howard", "Cooper", "Wood", "Black", "Gray", "Ross", "Murphy", "Watson", "Rodriguez", "Peterson", "Sam", "Hernandez", "Foster", "Curley", "Turner", "Sanders", "Lowery", "Brooks", "Peters", "Spencer"}; //100

string asianLastNames[LNAME_NUM] = {"Nguyen", "Lee", "Kim", "Patel", "Tran", "Chen", "Wong", "Le", "Yang", "Wang", "Chang", "Chan", "Pham", "Li", "Park", "Singh", "Lin", "Liu", "Wu", "Huang", "Lam", "Huynh", "Ho", "Choi", "Yu", "Shah", "Chung", "Khan", "Zhang", "Vang", "Truong", "Ng", "Phan", "Lim", "Xiong", "Vu", "Cheng", "Cho", "Vo", "Tang", "Ngo", "Chu", "Lu", "Kang", "Ly", "Hong", "Dang", "Hoang", "Do", "Chin", "Tan", "Lau", "Bui", "Kaur", "Han", "Ma", "Duong", "Leung", "Yee", "Song", "Cheung", "Ali", "Shin", "Ahmed", "Yi", "Thao", "Lai", "Hsu", "Fong", "Reyes", "Sun", "Chow", "Young", "Liang", "Lo", "Hwang", "Santos", "Cruz", "Oh", "Sharma", "Chau", "Garcia", "Kumar", "Xu", "Desai", "Thomas", "Hu", "Luu", "Zhou", "Dinh", "Yoon", "Trinh", "Tam", "Luong", "Chong", "Chiu", "Zheng", "Cao", "Zhu"}; //100

//Pacific islanders will share Asian Last Names, due to naming overlaps.  Mixed people will pick from all the names, at random.
//For the sake of time, there will be no middle eastern name database: they will pick from the pool of native and hispanic names.
//For the purpose of time, African-Americans and africans will share the Native American last names, since they overlap anyway.

//OCCUPATIONS
//Source: http://www.occupationsguide.cz/en/abecedni/abecedni.htm, comprehensive list.
string occupations[OCCUPATION_NUM] = {"Actor", "Actuary", "Administrative worker", "Advertising Manager", "Aerial Rigger", "Agricultural Adviser", "Agricultural Machinery Mechanic", "Agronomist", "Air Traffic Controller", "Air Traffic Safety Technician", "Aircraft Instrument Technician", "Aircraft Mechanic", "Airline Clerk", "Munitions Worker", "Animal Technician", "Animator", "Anthropologist", "Applications Manager", "Archeologist", "Architect", "Architectural Conservation Officer", "Art Critic" "Windowpane Maker", "Locksmith", "Art Photographer", "Art Restorer", "Legal Assistant", "Artificial Florist", "Artistic Promotions Manager", "Assessor", "Assistant Housekeeper", "Assistant Printing Worker", "Astrologer", "Astronomer", "Athlete", "Auctioneer", "Audio Graphic Designer", "Auditor", "Auto-electrician", "Baker", "Bank clerk",	 "Banking expert", "Barber", "Bartender", "Basket-maker", "Beautician",	 "Beekeeper", "Bibliographer", "Biochemist", "Biologist", "Biotechnologist", "Biscuit Maker", "Explosives expert", "Blasting Works Engineer", "Boiler operator", "Boilermaker", "Bookbinder", "Bookkeeper", "Bookmaker", "Botanist", "Brewer", "Bricklayer", "Broadcaster", "Brush-maker", "Builder", "Building electrician", "Civil engineer", "Butcher", "Butler", "Button maker", "Cab/taxi dispatcher", "Cabinet maker", "Cable car driver", "Cable maker", "Camera Mechanic", "Camera operator", "Canning Worker", "Capital Markets clerk/officer", "Captain of an Aircraft", "Car Mechanic", "Car Service Worker", "Care Assistant", "Diplomat", "Career Adviser", "Cartaker", "Carpenter", "Cartographer", "Cellulose Operator", "Ceramic Model Maker", "Ceramic painter", "Potter", "Ceramics Maker", "Charter Agent", "Cheese maker", "Chemical Industries Operative", "Chemical industry production manager", "Chemical Lab Technician",	"Chemical researcher", "Chemical technologist", "Chief/senior guard", "Children's nurse", "Chimney Sweep", "Choir Master", "Choreographer", "Circus Performer", "Cleaner", "Clerk", "Coffee Roaster", "Café owner", "Commentator", "Commercial Lawyer", "Company Lawyer", "Composer", "Computer Engineer", "Computer Equipment Operator", "Computer Network Manager", "Computer Programmer", "Concrete worker", "Orchestra Conductor", "Train Conductor", "Confectioner", "Conservator", "Construction carpenter/joiner", "Site manager", "Cook", "Corrosion control fitter", "Court executive officer", "Craft ceramicist", "Craft Gilder", "Craft glass etcher", "Craft glassmaker", "Craft metal founder and chaser", "Crane Operator", "Cooper", "Criminal Investigator", "Crop treater", "Customs officer", "Cutler", "Dairy Worker", "Dance Teacher", "Dancer", "Data transfer appliance technician", "Debt Collector", "Decorator", "Dental Assistant", "Dental technician", "Dentist", "Dietician", "Digger", "Director", "DJ", "Dish washer", "Dispatch clerk", "Dispatcher", "Diver", "Dog trainer", "Doorkeeper", "Driller", "Driver", "Driving Instructor", "Dust Control Technician", "Ecologist", "Economist", "Editor", "Educational Methods Specialist", "Electrical and power systems design engineer", "Electrical equipment design engineer", "Electrical equipment inspector", "Electrical mechanic", "Electrician", "Electroceramic production operative", "Electronic equipment mechanic", "Galvanizer", "Employment agent", "Enamel worker", "Engineering fitter", "Engineering maintenance", "Entertainment Officer", "Environmental Inspector", "Ergonomist", "Ethnographer", "Exhibitions production manager",	"Faith healer", "Farm worker", "Farmer", "Fashion Designer", "Feed production operator", "Film Critic", "Film designer", "Film or videotape editor", "Film Projectionist", "Financial Analyst", "Financial Officer", "Fine artist", "Firefighter", "Fire Inspector", "Fish Farmer", "Fish Warden", "Fisherman", "Flight attendant", "Flight engineer", "Floor fitter", "Plant grower", "Flying instructor", "Food industry production manager", "Food industry technologist", "Foreign exchange clerk", "Forester", "Forestry worker", "Fortune Teller", "Foster parent", "Foundry worker", "Fringe/trimmings maker", "Fruit farmer", "Funeral service worker", "Fur coat seamstress", "Furnace operator", "Furrier", "Gardener", "General labourer", "Geneticist", "Geographer", "Geological surveying equipment mechanic", "Geologist", "Geomechanic technician", "Geophysicist", "Glass decorator", "Glass jewellery maker", "Glass making machine operator", "Glass melter", "Glass painter", "Glassworker", "Glazier", "Goldsmith", "Government licensing official", "Graphic designer", "Gravedigger", "Guide", "Gunsmith", "Hand embroiderer", "Hand lacemaker", "Harbour guard",	"Harpooner", "Hatter", "Heating and ventilating fitter", "Heating engineer", "Herbalist", "High-rise work specialist", "Historian", "Horse Trainer", "Host", "Hotel Porter", "Hotel receptionist", "Hydrologist", "Ice-cream maker", "Image consultant", "Industrial designer", "Information assistant", "Insulator", "Insurance Clerk", "Interior designer", "Interpreter and translator", "Investment Clerk", "Jeweller", "Jewellery maker", "Joiner and cabinetmaker", "Judge", "Archivist", "Keeper of Animals", "Knitter", "Land surveyor", "Landscape architect", "Laundry worker", "Lecturer", "Librarian", "Lifeguard", "Lift attendant", "Lift fitter", "Lighting technician", "Lightning conductor fitter", "Lithographer", "Livestock farmer", "Lottery ticket street vendor", "Machine shop worker", "Machinery inspector", "Maker of non-woven textiles", "Make-up artist", "Management accountant", "Management consultant", "Manager", "Marine engineer", "Marketing manager", "Master of ceremonies", "Materials handler", "Mathematician","Medical laboratory assistant", "Mechanic",	 "Mechatronic engineer", "Metal engraver", "Steelworker", "Metallurgist", "Meteorologist", "Metrologist",	 "Microbiologist", "Midwife", "Miller", "Milling-machine operator", "Mine rescue service mechanic", "Mine ventilation technician", "Miner", "Mining air control technician", "Mining electrician", "Mining machine operator", "Mining rescue worker", "Mining/minerals surveyor", "Model", "Modeller", "Vehicle Mechanic", "Mountain Guide", "Multimedia designer", "Web Designer", "Police Officer", "Communal Service Worker", "Curator", "Music director", "Musical Instrument Technician", "Musician", "Nanny", "Naturalist", "Journalist", "Nuclear power station operator", "Nurse", "Nutritionist",	 "Online customer services operator", "Operational analyst/researcher", "Optical instrument mechanic", "Orthopaedic shoemaker", "Prosthetist", "Packer", "Paediatrician", "Palmists", "Paper worker", "Paramedic", "Patent agent", "Road Worker", "Pawnbroker", "Manicurist", "Personnel Officer", "Pest control officer", "Pharmaceutical operator", "Pharmaceutical laboratory technician", "Pharmacist", "Philosopher", "Photographer", "Physicist", "Physiotherapist", "Piano tuner", "Pilot", "Pizza maker", "Plumber", "Plywood maker", "Detective", "Political scientist", "Pollster", "Post office counter clerk", "Postal service worker", "Mail worker",  "Power engineering specialist", "Power station supervisor", "Public relations officer", "Pricing officer", "Priest", "Primary school teacher", "Printer", "Prison guard", "Private detective", "Producer", "Product designer", "Production manager", "Soldier",	 "Property manager", "Psychiatrist", "Psychologist", "Psychotherapist", "Public relations manager", "Publican", "Publisher", "Quality inspector", "Radio and TV technician",		 "Radiographer", "Rail transport worker", "Rail vehicle mechanic", "Rail Mecahnic", "Railway guard", "Ticket Clerk", "Rail Worker",	 "Real Estate Agent", "Referee", "Registrar", "Road Sign Assistant", "Road transport technician", "Rolling-mill operator", "Roofer", "Maid", "Tire fitter", "Safety engineer", "Salesman", "Sales Manager",	 "Scaffolder", "Scene painter", "Scene-shifter", "Script editor", "Sculptor", "High school teacher", "Secretary", "Security guard", "Service mechanic/ repairer", "Sewage Cleaner", "Shepherd",	 "Ship's captain", "Ship's officer", "Shoemaker", "Cashier", "Singer", "Social worker", "Sociologist", "Jehova's Witness", "Songwriter", "Sound effects technician", "Sound engineer", "Speech therapist", "Stablehand", "Stage manager", "State attorney", "Statistician", "Stockbroker", "Stonemason", "Storekeeper", "Stuntperson", "Systems designer", "Systems engineer",	 "Tailor", "Tamer",	 "Tanner", "Tannery worker", "Tax specialist", "Technical editor", "Emergency Dispatcher", "Telecommunications mechanic", "Teller", "Textile worker", "Doctor", "Optician", "Tinsmith", "Tobacco technologist", "Tool maker", "Town planner", "Mall Cop", "Sports Coach", "Tutor", "Usher", "Traceur", "Veterinarian", "Wine Grower", "Waiter",	"Waste incineration plant worker", "Water supply and distribution manager", "Watchmaker", "City Guard", "Weaver", "Weaver", "Weigher", "Welder", "Well digger", "Whaler", "Window cleaner", "Wood Carver", "Woodcutter", "Worker", "Student"};

//Random facts about people.  Some from Watch_Dogs, most are my own ideas.  Just for fun, but meant to emulate information that could be obtained from public online accounts.
string facts[FACT_NUM] = {"Trolls online political forums", "Attempted suicide", "Animal lover", "Denies evolution", "Denies Climate Change", "Illegal Immigrant", "Curious about Walls", "Curious about Programming", "Curious about Hacking", "Feeling happy", "Feeling sad", "Feeling stupid", "Feeling betrayed", "Feeling mad", "Changed relationship status", "Newlywed", "Had recent break-up", "Recently entered a relationship", "Had over ten relationships within this month", "Identifies as Homosexual", "Identifies as Bisexual", "Identifies as a Queer", "Identifies as a Heterosexual", "Political Activist", "Part of LGBTQ Community", "HIV Positive", "Illiterate", "Pro-war Activist", "Pro-choice Lobbyist", "Pro-life lobbyist", "Activist", "Hacktivist", "Member of Anonymous", "Participated in LulzSec raids", "Below average SAT score", "Likes Rare Art", "Runs an Animal Shelter", "Long-time Vegan", "Long-time Vegetarian", "Victim of Childhood Abuse", "Has Long Criminal Record", "Registered Sex Offender", "Targeted by \"The Brotherhood\"", "Chosen by the Thug Life", "Likes to post \"Dank Memes\"", "Dog Lover", "Cat Lover", "Bunny Lover", "MLG 360 Quickscoper", "MLG 360 Noscoper", "Hardscopes in First Person Shooters", "Member of a Gaming League", "Started a Gaming Clan", "Started an Overwatch League", "Frequent online search: \"Trump\"", "Frequent online search: \"John Cena\"", "Frequent online search: \"Clinton\"", "Frequent online search: \"How to rickroll\"", "Frequent online search: \"How to enter farms\"", "Voted for Trump", "Voted for Clinton", "Voted for Stein", "Voted for Gary Johnson", "Supports Bernie Sanders", "Banned from Sci-fi Convention", "Recent conviction", "Shoplifter", "Fan of \"Secular Talk\"", "Fan of \"Game of Thrones\"", "Fan of \"House of Cards\"", "Fan of \"Mr. Robot\"", "Fan of \"Tool\"", "Fan of \"Metallica\"", "Fan of \"Watch Dogs\"", "Fan of \"Assassin's Creed\"", "Fan of \"Far Cry\"", "Fan of \"Overwatch\"", "Fan of \"Video Games\"", "Fan of Classical Music", "Fan of Hip-Hop Music", "Fan of Electronic Music", "Fan of Rock Music", "Donates to Women's Rights Organizations", "Habitual Rick Roller", "Toastmaster", "Believes Jesus was an Alien Spy", "Has Penpal", "Undergoing Chemotherapy", "Diagnosed with Cancer", "Top player in fighting games", "Upcoming Vacation", "Just got Back from Vacation", "Joined Apocalypse Survival Group", "Attended Ninja Convention", "Likes Fox News", "Watches CNN", "Martial Artist", "Has 3 Kids", "Has 5 Kids", "Lives with Mother", "Has Multiple Allergies", "Under Investigation"}; //102

//Functions to generate separate parts of the profile
string generateName(int gender, int race){
    //Remember: White = 0, Hispanic/Latino = 1, Black = 2, Native American = 3, Asian = 4, Islander = 5, Middle eastern = 6, Mixed = 7.
    srand(time(0));
    string firstname;
    string lastname;
    //Generate first name, based on gender.
    if(gender == 1){
        firstname = boyFirstNames[rand() % FNAME_NUM];   
    }
    else if(gender == 2){
        firstname = girlFirstNames[rand() % FNAME_NUM];
    }
    else{
        cout << "Problem creating first name: Invalid gender.\nGender Value: " << gender << endl;;
        firstname = "ERROR";
    }
    //Generate last name, using ethnicity
    if(race == 0){
        lastname = caucasianLastNames[rand() % LNAME_NUM];
    }
    else if(race == 1){
        lastname = hispanicLastNames[rand() % LNAME_NUM];
    }
    else if(race == 2 || race == 3){
        lastname = nativeLastNames[rand() % LNAME_NUM];
    }
    else if(race == 4 || race == 5){
        lastname = asianLastNames[rand() % LNAME_NUM];
    }
    else if(race == 6){
        if((rand() % 2 + 1) == 1){
            lastname = nativeLastNames[rand() % LNAME_NUM];
        }
        else{
            lastname = hispanicLastNames[rand() % LNAME_NUM];
        }
    }
    else if(race == 7){
        int option = rand() % 4;
        if(option == 0){
            lastname = caucasianLastNames[rand() % LNAME_NUM];
        }
        else if(option == 1){
            lastname = hispanicLastNames[rand() % LNAME_NUM];
        }
        else if(option == 2){
            lastname = asianLastNames[rand() % LNAME_NUM];
        }
        else if(option == 3){
            lastname = nativeLastNames[rand() % LNAME_NUM];
        }
        else{
            cout << "Problem creating last name: Mixed Race Random Overload.\n";
            string lastname = "ERROR";
        }
    }
    else{
        cout << "Problem creating last name: Invalid race/ethnicity.\nRace value: " << race << endl;
        string lastname = "ERROR";
    }
    
    //Compile that into a full name
    string name = "";
    name += firstname;
    name += " ";
    name += lastname;
    //Return statement
    return name;
}
string generateFact(){
    srand(time(0));
    return facts[rand() % FACT_NUM];
}
string generateOccupation(){
    srand(time(0));
    return occupations[rand() % OCCUPATION_NUM];
}
