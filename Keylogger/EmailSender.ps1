Param( [String]$Att, [String]$Subj, [string]$Body )

Function Send-Email
{
    Param(
            [Parameter(`
            Mandatory=$true)]
        [String]$To, 
            [Parameter(`
            Mandatory=$true)]
        [String]$From,
            [Parameter(`
            Mandatory=$true)]
        [String]$Password, 
            [Parameter(`
            Mandatory=$true)]
        [String]$Subject,
            [Parameter(`
            Mandatory=$true)]
        [String]$Body,
            [Parameter(`
            Mandatory=$true)]
        [String]$attachment
        )

    try
    {
        $Msg = New-Object System.Net.Mail.MailMessage($From, $To, $Subject, $Body)
        $Srv = "undonecayon@gmail.com"
        if ($attachment -ne $null)
        {
            try 
            {
                $Attachments = $attachment -split ("\:\:");

                ForEach($val in $Attachments)
                {
                    $attch = New-Object System.Net.Mail.Attachment($val)
                    $Msg.Attachments.Add($attch)
                }
            }
            catch 
            {
                exit 2;#Error
            }

            $Client = New-Object Net.Mail.SmtpClient($Srv, 587)
            $Client.EnableSsl = $true
            $Client.Credentials = New-Object System.Net.NetworkCredential($From.Split("@")[0], $Password);
            $Client.Send($Msg)
            Remove-Variable -Name Client
            Remove-Variable -Name Password
            exit 7;#Everything went okay
        }
}

catch 
    {
        exit 3;#Error
    } 
}

try 
{
    Send-Email
        -attachments $Att
        -To "Address of the recipient"
        -Body $Body
        -Subject $Subj
        -password "haha"
        -From "Address of the Sender"
}
catch
{
    exit 4;
}