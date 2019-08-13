Predi Dragos 311CC

In primul rand, pe aceasta cale as vrea sa multumesc laborantilor de SD in general. 
Pana acum am avut o experienta foarte placuta cand a venit vorba de materiile de informatica
Oamenii implicati sunt in general amabili si deschisi sa te ajute si astfel, as vrea sa va multumesc
pentru tot efortul depus. 

In al doilea rand, deoarece mi-am dozat timpul prost si am avut o abordare proasta, codul este destul de "verbose"
nu am avut timp sa il modularizez si nu m-am atins deloc de memory leak-uri. Am crezut ca pot sa fac tot 
programul si mai apoi sa ma ocup de memorie, dar acum imi dau seama ca nu asa se abordeaza. Sunt constient de
aceste probleme

In al treilea rand: functiile folosite la implementarea structurilor de date le-am luat de la laborator,
Scheletul lor este creat de Mihai Nan, eu decat le-am modificat incat sa poate fi folosite pentru tema. 
Insa el mi-a zis ca este ok acest lucru si nu trebuiesc reimplementate de mine integral.

***Mod de implementare task-uri***:

task1: pentru creearea grafului am folosit o lista auxiliara in care am tinut toate datele (id, parinte, nr adrese,
adresele si utilizatorii) si o coada in care am retinut nodul parinte si adresa lui in graf (ii adaug copiii cu adresele lor 
apoi il sterg din coada, s.a.m.d).

task2: in functia pentru task1, creez o adoua coada cu toate frunzele grafului. De aceasta coada ma folosesc 
pentru a adauga adresele in nodurile parinte, plec de la frunze in sus

task3: pur si simplu verific daca exista adresa, daca nu exista ii fac cache si urc in parinte


Functiile de implementare structuri de date sunt fiecare in fisierele lor, iar numele sunt destul de sugestive,
deci nu am mai simtit nevoia sa le comentez

Am incercat sa comentez cat mai bine codul de aceea am lasat README-ul mai sumar.