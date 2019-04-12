# SmartCoaster
Smart coaster project for graduate Embedded System Design course at FAU using ASF on Atmel SAMD21J18A (SAMD21 XPLAINED PRO board)



Setting up the project in Atmel Studio 7:

1) Create a New GCC C ASF Board Project

2) Add the following modules using the ASF Wizard and click Apply:

    - Generic Board Support
    
    - Sleep Manager
    
    - Delay Routines (cycle)
    
    - AC (callback)
    
    - ADC (callback)
    
    - EXTINT (callback)
    
    - PORT
    
    - SERCOM USART (callback)
    
    - SYSTEM
    
    - TC (callback)
    
    - TCC (callback)
    
    - stdio

3) Navigate to your Atmel Studio project's src folder (from command line or git client, I use VSC's built-in git client)
   and copy/paste the following commands:
   
   git init
   
   git remote add origin 
   
   git pull
