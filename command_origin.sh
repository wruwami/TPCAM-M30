#!/bin/bash

settings_conf_text_content="[Behavior]
AutoSelectionDelay=600
BookmarkOpenMethod=current_tab
ConfirmDelete=true
ConfirmTrash=false
NoUsbTrash=false
QuickExec=true
SelectNewFiles=false
SingleClick=false
UseTrash=true

[Desktop]
BgColor=#000000
DesktopCellMargins=@Size(3 1)
DesktopIconSize=48
DesktopShortcuts=Home, Trash, Computer, Network
FgColor=#ffffff
Font="Ubuntu,12,-1,5,50,0,0,0,0,0"
HideItems=false
LastSlide=
ShadowColor=#000000
ShowHidden=false
ShowWmMenu=false
SlideShowInterval=0
SortColumn=name
SortFolderFirst=true
SortOrder=ascending
Wallpaper=/home/firefly/Downloads/screen.jpg
WallpaperDirectory=
WallpaperMode=stretch
WallpaperRandomize=false

[FolderView]
BackupAsHidden=false
BigIconSize=48
CustomColumnWidths=@Invalid()
FolderViewCellMargins=@Size(3 3)
HiddenColumns=@Invalid()
Mode=icon
ShadowHidden=false
ShowFilter=false
ShowFullNames=false
ShowHidden=false
SidePaneIconSize=24
SmallIconSize=24
SortCaseSensitive=false
SortColumn=name
SortFolderFirst=true
SortOrder=ascending
ThumbnailIconSize=128

[Places]
PlacesApplications=true
PlacesComputer=true
PlacesDesktop=true
PlacesHome=true
PlacesNetwork=true
PlacesRoot=true
PlacesTrash=true

[Search]
searchContentCaseInsensitive=false
searchContentRegexp=true
searchNameCaseInsensitive=false
searchNameRegexp=true
searchRecursive=false
searchhHidden=false

[System]
Archiver=ark
FallbackIconThemeName=oxygen
OnlyUserTemplates=false
SIUnit=false
SuCommand=lxqt-sudo %s
TemplateRunApp=false
TemplateTypeOnce=false
Terminal=qterminal

[Thumbnail]
MaxThumbnailFileSize=4096
ShowThumbnails=true
ThumbnailLocalFilesOnly=true

[Volume]
AutoRun=true
CloseOnUnmount=true
MountOnStartup=true
MountRemovable=true

[Window]
AlwaysShowTabs=false
FixedHeight=480
FixedWidth=640
LastWindowHeight=480
LastWindowMaximized=false
LastWindowWidth=640
PathBarButtons=true
RememberWindowSize=true
ShowMenuBar=true
ShowTabClose=true
SidePaneMode=places
SplitView=false
SplitterPos=275
"
panel_desktop_text_content="[Desktop Entry]
Type=Application
Name=Panel
TryExec=lxqt-panel
Exec=lxqt-panel
OnlyShowIn=LXQt;
X-LXQt-Module=true

Name[ar]=اللوحة
Name[ca]=Tauler
Name[cs]=Panel
Name[da]=Panel
Name[de]=Bedienfeld
Name[el]=Πίνακας
Name[eo]=Panelo
Name[es]=Panel
Name[es_VE]=Panel
Name[eu]=Panela
Name[fi]=Paneeli
Name[fr]=Tableau de bord
Name[hu]=Panel
Name[hu_HU]=Panel
Name[ia]=Panello
Name[it_IT]=Pannello
Name[ja]=パネル
Name[lt]=Skydelis
Name[nl]=Paneel
Name[pl]=Panel
Name[pt]=Painel
Name[pt_BR]=Painel
Name[ro_RO]=Panou
Name[ru]=панель
Name[ru_RU]=Панель
Name[sl]=Pult
Name[th_TH]=พาเนล
Name[tr]=Panel
Name[uk]=Панель
Name[zh_CN]=面板
Name[zh_TW]=面板
"

echo "$settings_conf_text_content" > "/home/firefly/.config/pcmanfm-qt/lxqt/settings.conf"
echo "$panel_desktop_text_content" > "/etc/xdg/autostart/lxqt-panel.desktop"