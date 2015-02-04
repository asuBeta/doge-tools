#!/bin/sh

# this script will remove microsoft office

# Display a simple welcome message first.
echo ""
echo "Welcome to the microsoft office uninstaller script."
echo ""

# Display the sudo usage instructions and execute the command.
echo "The uninstallation processes requires administrative privileges."
echo "You'd better run it with sudo..."
echo ""

my_default_prompt=0

if test "$my_default_prompt" != "Yes"; then
    echo "Do you really want to uninstall microsoft office (Yes/No)?"
    read my_answer
    if test "$my_answer" != "Yes"  -a  "$my_answer" != "YES"  -a  "$my_answer" != "yes"; then
        echo "Aborting uninstall...\n"
        echo "Aborted."
        exit 2;
    fi
    echo ""
fi

osascript -e 'tell application "Microsoft Database Daemon" to quit'

# the following steps are based on microsoft's offical site
# you can find it on http://support.microsoft.com/kb/2398768/ja

# step 2
rm -R '/Applications/Microsoft Communicator.app/'
rm -R '/Applications/Microsoft Messenger.app/'
rm -R '/Applications/Microsoft Office 2011/'
rm -R '/Applications/Remote Desktop Connection.app/'

# step 3
rm -R '~/Library/Preferences/com.microsoft*'
rm -R '/Library/LaunchDaemons/com.microsoft.office.licensing.helper.plist'
rm -R '/Library/PrivilegedHelperTools/com.microsoft.office.licensing.helper'

# step 4
#rm -R '/Library/Preferences/com.microsoft.office.licensing.plist'
rm -R '~/Library/Preferences/ByHost/com.microsoft*'

# step 5
rm -R '/Library/Application Support/Microsoft'

# step 6
rm -R '/private/var/db/receipts/com.microsoft.office*'

# step 7
rm -R '~/Library/Application Support/Microsoft/Office'

# step 8
rm -R '/Library/Fonts/Microsoft/'

# others
rm -R /Library/Automator/*Excel*
rm -R /Library/Automator/*Office*
rm -R /Library/Automator/*Outlook*
rm -R /Library/Automator/*PowerPoint*
rm -R /Library/Automator/*Word*
rm -R '/Library/Automator/Add New Sheet to Workbooks.action'
rm -R '/Library/Automator/Create List from Data in Workbook.action'
rm -R '/Library/Automator/Create Table from Data in Workbook.action'
rm -R '/Library/Automator/Get Parent Presentations of Slides.action'
rm -R '/Library/Automator/Get Parent Workbooks.action'
rm -R '/Library/Automator/Set Document Settings.action'

OFFICERECEIPTS=$(pkgutil --pkgs=com.microsoft.office*)
for ARECEIPT in $OFFICERECEIPTS
do
	pkgutil --forget $ARECEIPT
done

hostid=`whoami`
echo "Microsoft Office files in /Users/${hostid}/ will not be deleted..."
echo "You can delete them by yourself if needed.\n"

echo "Done."
exit 0;
