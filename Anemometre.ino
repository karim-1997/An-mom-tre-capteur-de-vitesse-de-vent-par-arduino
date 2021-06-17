#define PI 3.14
float V;
unsigned long tempsDebut;  // passage précédent de l'aimant

int etatPrecedent;  // lors de du dernier passage dans le loop,
                    // l'aimant était là, ou pas? 

void setup() {
  pinMode(3, INPUT);   // interrupteur Reed à la pin 3
  pinMode(8,OUTPUT);  // LED indicatrice à la pin 8
  Serial.begin(9600);  // moniteur série
  etatPrecedent = digitalRead(3); // on vérifie si l'aimant est là ou pas
}

void loop() {

  int etat, delai;
  unsigned long tempsFin;

  etat = digitalRead(3);  // on vérifie si l'aimant est là ou pas
  
  digitalWrite(8,etat);

  if ((etat) && (!etatPrecedent)){ // l'aimant vient d'arriver
    if (tempsDebut > 0){  // nous connaissons le moment du début de ce tour
      tempsFin = millis();  
      delai = tempsFin - tempsDebut;  // durée du tour qui vient de se terminer
      Serial.print("Periode :" );
      Serial.print(delai);
      V=3.6*1000*2*PI*0.1/delai;
      Serial.print("  miliseconsecondes,  Vitesse :");    
      Serial.print(V);
      Serial.println(" km/h");        
    }
    
    tempsDebut = tempsFin;  // mise à jour de la variable
  }
  
  etatPrecedent = etat;  // mise à jour de la variable
}
