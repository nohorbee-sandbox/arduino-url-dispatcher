#include <HashMap.h>
#include <Resource.h>



const byte SIZE_URIs = 6; // constant until resolve what's going on with sizeof

void setup() {
  
  Serial.begin(9600);
  char* url[] = {
  "/resourceType1",
  "/resourceType2",
  "/resourceType1/1",
  "resourceType1/resourceType11",
  "/resourceType1/3/resourceType13",
  "/resourceType1/resourceType11/2"
};

  struct Resource URIs[SIZE_URIs];
  URIs[0].uri = "/resourceType1";
  URIs[0].handler = handler1;
  URIs[1].uri = "/resourceType2";
  URIs[1].handler = handler2;
  URIs[2].uri = "/resourceType1/resourceType11/{:resourceType11Id}";
  URIs[2].handler = handler3;
  URIs[3].uri = "/resourceType1/{:resourceType1Id}";
  URIs[3].handler = handler4;
  URIs[4].uri = "/resourceType1/{:resourceType1Id}/resourceType13";
  URIs[4].handler = handler5;
  URIs[5].uri = "/resourceType1/resourceType12/{:resourceType12Id}/child";
  URIs[5].handler = handler6;

//  lookup(url[0], URIs);
//  lookup(url[1], URIs);
//  lookup(url[2], URIs);
//  lookup(url[3], URIs);
//  lookup(url[4], URIs);
  lookup(url[5], URIs);
  //URIs[5].handler("a","b");


  /* uri 
   http://host/resourceType1
   http://host/resourceType2
   http://host/resourceType1/resourceType11
   http://host/resourceType1/{:resourceType1Id}
   http://host/resourceType1/{:resourceType1Id}/resourceType13
   http://host/resourceType1/resourceType12/{:resourceType12Id}
   */

}

int lookup(char* url,struct Resource* URIs) {
  
  Serial.print("Parsing URL: ");
  Serial.println(url);
  int i=0;
  int foundPosition = -1;
  byte wildcardsCount = 255;
  byte prevWildcardsCount = 255;
  for(i;i<SIZE_URIs;i++) {
    Serial.print("Testing match URI: ");
    Serial.println(URIs[i].uri);
    Serial.print("VS. URL: ");
    Serial.println(url);
    char* urlTok;
    char* uriTok;
    char* uriToTokenize = strdup(URIs[i].uri);
    char* urlToTokenize = strdup(url);
    char* ptrURI;
    char* ptrURL;
    
    
    urlTok = strtok_r(urlToTokenize, "/", &ptrURL);
    uriTok = strtok_r(uriToTokenize, "/", &ptrURI);
    bool match = true;
    while((urlTok != NULL || uriTok != NULL) && match) {
      if (strcmp(urlTok,uriTok)!=0) {
        if(checkWildcard(uriTok)) {
          wildcardsCount++;
        } else {
          match=false;
        }
      }
      urlTok = strtok_r(NULL, "/", &ptrURL);
      uriTok = strtok_r(NULL, "/", &ptrURI);
    }
    
    if(match) {
        Serial.print("THIS ONE MATCH: ");
        Serial.print(URIs[i].uri);
        if(wildcardsCount<prevWildcardsCount) {
          Serial.print(" AND IT HAS THE LESS WILDCARDS COUNT THIS FAR --> FOUND POSITION (i): ");
          Serial.print(i);
          Serial.print(" WildCardsCount: ");
          Serial.println(wildcardsCount);
          prevWildcardsCount = wildcardsCount;
          foundPosition = i;
        }
      }
    
  }
  if (foundPosition>-1) {
    Serial.print("Found pattern for URL: ");
    Serial.print(url);
    Serial.print(" is ");
    Serial.println(URIs[foundPosition].uri);
  } else {
    Serial.println("The URL doesn't match any URI template");
  }
  
}

bool checkWildcard(char* toCheckorig) {
  String toCheck = String(toCheckorig);
  Serial.print("Checking if wildcard for: ");
  Serial.println(toCheck);
  if(!(toCheck.length()>0)) { Serial.println("empty string is not a wildcard"); return false; }// empty string is not a wildcard 
  if(toCheck[0]=='{'  && toCheck[1]==':' && toCheck[toCheck.length()-1]=='}') { 
    Serial.println("It' a wildcard!!!"); 
    return true; 
  }
  return false;
}

void loop() {
}

void handler1(String p1, String p2) {
}
void handler2(String p1, String p2) {
}
void handler3(String p1, String p2) {
}
void handler4(String p1, String p2) {
}
void handler5(String p1, String p2) {
}
void handler6(String p1, String p2) {
}


