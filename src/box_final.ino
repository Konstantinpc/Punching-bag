#include <LiquidCrystal.h>//lcd
#include <IRremote.h>//remote control

//remote control
const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;

// initialize the library with the numbers of the interface pins
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// the pin that the pushbutton is attached to
const int  buttonPin = 6;    

// Variables will change:
int c=0;//number of rounds
int p=0;//round time
int e=0;//rest
int k=1;
int i=0;
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button
unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
unsigned long currentMillis_1=0;
unsigned long t_period=60000;

unsigned long period=180000;
int small_period=180;
int small_period_m=3;
int small_period_s=0;
int timeout_period=60;
int timeout_period_m=1;
int timeout_period_s=0;
int y=0;
float rounds[256];
int sum=0;
void mainy();
void setup() {
	irrecv.enableIRIn();
	irrecv.blink13(true);
	// set up the LCD's number of columns and rows:
	lcd.begin(16, 2);
	pinMode(buttonPin, INPUT);
	// initialize serial communication:
	Serial.begin(9600);
	// Print a message to the LCD.
	int t=0;
	lcd.setCursor(3, 0);
	lcd.print("Welcome to");
	delay(1000);
	lcd.clear();
	lcd.setCursor(3, 0);
	lcd.print("Boxing bag");
	delay(1000);
	lcd.clear();
	while(t==0){
	lcd.setCursor(2, 0);
	lcd.print("Press a key!");
	delay(750);
	lcd.clear();
	delay(550);
	if (irrecv.decode(&results)){
	         
	      if (results.value == 0XFFFFFFFF)
	        results.value = key_value;
	        t++;
	      
	      key_value = results.value;
	      irrecv.resume();
	      delay(150); 
	      
	}
	
	
	
	}
	
	lcd.clear();
	while(c!=1){
	if (irrecv.decode(&results)){
	
	      if (results.value == 0XFFFFFFFF)
	        results.value = key_value;
	
	      switch(results.value){
	        case 0xFFA25D:
	        Serial.println("CH-");
	        break;
	        case 0xFF629D:
	        Serial.println("CH");
	        break;
	        case 0xFFE21D:
	        Serial.println("CH+");
	        break;
	        case 0xFF22DD:
	        Serial.println("|<<");
	        break;
	        case 0xFF02FD:
	        Serial.println(">>|");
	        c=1;
	        delay(500);
	        case 0xFFC23D:
	        Serial.println(">|");
	        break ;               
	        case 0xFFE01F:
	        Serial.println("-");
	        
	        if(k>1){
	          k--;
	        }  
	        break;
	          
	        case 0xFFA857:
	        Serial.println("+");
	        k++;
	        
	        case 0xFF906F:
	        Serial.println("EQ");
	        break ;  
	        case 0xFF6897:
	        Serial.println("0");
	        break ;  
	        case 0xFF9867:
	        Serial.println("100+");
	        break ;
	        case 0xFFB04F:
	        Serial.println("200+");
	        break ;
	        case 0xFF30CF:
	        Serial.println("1");
	        break ;
	        case 0xFF18E7:
	        Serial.println("2");
	        break ;
	        case 0xFF7A85:
	        Serial.println("3");
	        break ;
	        case 0xFF10EF:
	        Serial.println("4");
	        break ;
	        case 0xFF38C7:
	        Serial.println("5");
	        break ;
	        case 0xFF5AA5:
	        Serial.println("6");
	        break ;
	        case 0xFF42BD:
	        Serial.println("7");
	        break ;
	        case 0xFF4AB5:
	        Serial.println("8");
	        break ;
	        case 0xFF52AD:
	        Serial.println("9");
	        break ;      
	      }
	      key_value = results.value;
	      irrecv.resume();
	      delay(150); 
	      
	}
	lcd.setCursor(0, 0);
	lcd.print("Number of rounds");
	lcd.setCursor(7, 1);
	lcd.print(k);
	
	}
	lcd.clear();
	
	while(p!=1){
	if (irrecv.decode(&results)){
	
	      if (results.value == 0XFFFFFFFF)
	        results.value = key_value;
	
	      switch(results.value){
	        
	        case 0xFF02FD:
	        Serial.println(">>|");
	        p=1;
	        delay(500);
	   
	        case 0xFFE01F:
	        Serial.println("-");
	        
	        if(small_period>30.0){
	          small_period=small_period-30;
	          period=period-30000;  
	        }  
	        small_period_m=small_period/60;
	        small_period_s=small_period%60;
	        break;
	          
	        case 0xFFA857:
	        Serial.println("+");
	        small_period=small_period+30;
	        period=period+30000;
	        small_period_m=small_period/60;
	        small_period_s=small_period%60;
	        
	      }
	      key_value = results.value;
	      irrecv.resume();
	      
	}
	lcd.setCursor(1, 0);
	lcd.print("Time of round");
	if(small_period_m>9){
	  
	  lcd.setCursor(5, 1);
	  lcd.print(small_period_m);
	
	  }else{
	    lcd.setCursor(5, 1);
	    lcd.print("0");
	    lcd.setCursor(6, 1);
	    lcd.print(small_period_m);
	  }
	lcd.setCursor(7, 1);
	lcd.print(":");
	lcd.setCursor(8, 1);
	lcd.print(small_period_s);
	lcd.setCursor(9, 1);
	lcd.print("0");
	}
	lcd.clear();
	while(e!=1){
	if (irrecv.decode(&results)){
	
	      if (results.value == 0XFFFFFFFF)
	        results.value = key_value;
	
	      switch(results.value){
	        
	        case 0xFF02FD:
	        Serial.println(">>|");
	        e=1;
	        delay(500);
	   
	        case 0xFFE01F:
	        Serial.println("-");
	        
	        if(timeout_period>30.0){
	          timeout_period=timeout_period-30;
	          t_period=t_period-30000;  
	        }  
	        timeout_period_m=timeout_period/60;
	        timeout_period_s=timeout_period%60;
	        break;
	          
	        case 0xFFA857:
	        Serial.println("+");
	        timeout_period=timeout_period+30;
	        t_period=t_period+30000;
	        timeout_period_m=timeout_period/60;
	        timeout_period_s=timeout_period%60;
	        
	      }
	      key_value = results.value;
	      irrecv.resume();
	      
	}
	lcd.setCursor(1, 0);
	lcd.print("Time of rest");
	if(timeout_period_m>9){
	  
	  lcd.setCursor(5, 1);
	  lcd.print(timeout_period_m);
	
	  }else{
	    lcd.setCursor(5, 1);
	    lcd.print("0");
	    lcd.setCursor(6, 1);
	    lcd.print(timeout_period_m);
	  }
	lcd.setCursor(7, 1);
	lcd.print(":");
	lcd.setCursor(8, 1);
	lcd.print(timeout_period_s);
	lcd.setCursor(9, 1);
	lcd.print("0");
	}
	lcd.clear();
	startMillis=millis();

}

void loop() {
  

	if(y==0){ 
		mainy();
	}else{
	lcd.setCursor(3, 0);
		lcd.print("Statistics");
		delay(3000);
	lcd.clear();
	sum=0;
	for(int i=0; i<k; i++){
		
	
		if(i>10){
			lcd.setCursor(1, 0);
			lcd.print("Round ");
			lcd.print(i+1);
		}else{ 
			lcd.setCursor(2, 0);
			lcd.print("Round ");
			lcd.print(i+1);
			}
		   	
		lcd.setCursor(9, 0);
	
		   	lcd.print(" hits");
		   	lcd.setCursor(7, 1);
		lcd.print(int(rounds[i]));
		delay(2000);
		sum+=rounds[i];
		lcd.clear();
		lcd.setCursor(1, 0);
		lcd.print("Hit frequency");
		lcd.setCursor(4, 1);
		float hs=rounds[i]/small_period;
		lcd.print(hs);
		lcd.print(" h/s");
		delay(2000);
		lcd.clear();
		}
	lcd.clear();
	lcd.setCursor(3, 0);
	lcd.print("Total hits");
	lcd.setCursor(7, 1);
	lcd.print(sum);
	delay(2000);
	lcd.clear();
	}
  
}

void mainy(){
  unsigned long new_time;
  unsigned long tm;
  unsigned long small_tm;
  while(i<k){
    currentMillis=millis();
    
    if(i==0){
    	tm=4000;
    	small_tm=4;	
    }else{
    	
    	tm=t_period;
    	small_tm=timeout_period;
    	
    	}
    if(currentMillis-startMillis<tm){

         lcd.setCursor(4, 0);      
         lcd.print("Round ");
         lcd.setCursor(10, 0);
         lcd.print(i+1);
         lcd.setCursor(7, 1);
    	if((tm-(currentMillis-startMillis))/1000 >= 1){
    		if((tm-(currentMillis-startMillis))/1000 <10){
    			lcd.print(" ");
          lcd.print((tm-(currentMillis-startMillis))/1000);
    		}else{
          lcd.print((tm-(currentMillis-startMillis))/1000);
    		}
         }else if((tm-(currentMillis-startMillis))/1000 < 1) {
         	lcd.print("Go");
         	delay(1000);
         	lcd.clear();
         }
         	
         	

      
        
    }else{
    if(currentMillis-startMillis<period+tm){
      lcd.setCursor(0, 0);
     
      lcd.print("Time left: ");
      lcd.setCursor(11, 0);
      buttonState = digitalRead(buttonPin);
  
     
      new_time = (small_period+small_tm- ((currentMillis-startMillis) / 1000));
      small_period_m=new_time/60;
      small_period_s=new_time%60;  
      if(small_period_m>9){
        lcd.setCursor(11, 0);
        lcd.print(small_period_m);
        }else{
          lcd.setCursor(11, 0);
          lcd.print("0");
          lcd.setCursor(12, 0);
      lcd.print(small_period_m);
        }
      
      lcd.setCursor(13, 0);
      lcd.print(":");
      if(small_period_s<10){
           lcd.setCursor(14, 0);
            lcd.print("0");
           lcd.setCursor(15, 0);
           lcd.print(small_period_s); 
      }else{
     
      lcd.setCursor(14, 0);
      lcd.print(small_period_s);
      }
      //lcd.setCursor(15, 0);
      //lcd.print(" ");
      if (buttonState != lastButtonState) {
        // if the state has changed, increment the counter
        if (buttonState == HIGH) {
          // if the current state is HIGH then the button went from off to on:
          buttonPushCounter++;
          Serial.println("on");
          Serial.print("number of button pushes: ");
          Serial.println(buttonPushCounter);
        } else {
          // if the current state is LOW then the button went from on to off:
          Serial.println("off");
        }
        // Delay a little bit to avoid bouncing
        delay(50);
      }
      // save the current state as the last state, for next times through the loop
      lastButtonState = buttonState;
      
      lcd.setCursor(0, 1);
     
          lcd.print("Hits = ");
          lcd.setCursor(7, 1);
          lcd.print(buttonPushCounter);
      
    }
    
    
  else{
    rounds[i]=buttonPushCounter;
    buttonPushCounter=0;
    i++;
    
    lcd.clear();
    /*lcd.setCursor(3, 0);
    lcd.print("ROUND OVER");
    delay(1000);
    
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Hits = ");
    lcd.setCursor(10, 0);
    lcd.print(buttonPushCounter);
    delay(2000);
    lcd.clear();*/
    
    startMillis=currentMillis;
    if(i==k) y=1;    
    }
  }
}
}
