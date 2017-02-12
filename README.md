# Drupal751-with-module
Drupal 7.51 with module to upload and get properties of image. It includes a DLL and an .exe file based on C++

How to install:

1) Directly install it On XAMPP

1) Download it and put it in a folder under htdocs folder in XAMPP;
2) in the "database_sql" folder, the drupal75.sql file is SQL script; 
Import the .sql file on PHPMyAdmin to build database, user, tables and input data. 
After installed the database, this folder should be removed.
3) Then you can open the website on your browser.

2) Install Drupal 7.51 first and the install the module. 

Just download the module named "Process Image" 
in the "sites\all\modules" folder. And install it on your Drupal. And copy the two files to your root folder 
your drupal: CImgdll.dll, CImgClient.exe. And go to dashboard to active it. 

How to use it:

On the life bar in the front page, click the "Process Image" link, in the opened window, upload the image,
after submitted it, on the top, it will show the message. You can see the screen shot on the screenshot.png.

 
How to test:

Administrator: admin
Password: admin

1) login to the dashboard;
2) Go to Configuration >> Development >> Testing
3) Check the checkbox before "Images" on the list, then click "Run tests" button. 
