#
********************************************************************************
* License Information: Accord Global Technology Solutions Private Limited.
* 72 & 73, Krishna Reddy Colony, Domlur layout
* Bangalore - 560071, INDIA
* Licensed software and all rights reserved.
********************************************************************************
*
* Author(s): Arpit K @ AGTSPL
*
* 1.1
********************************************************************************
##

Project Title:- Using Qt Creator page with TreeView content, 
		select the text in the tree view to change the properties, 
		add checkbox next to tree content for multiple selection.

Motivation:-	To read any document model files like XML, html, svg. And
		arrange the document into Tree structure. Root items to be
		Selectable and selected Items to be Highlighted.

Build Status:-	The Build is made for both LINUX and WINDOWS environment.
		The Code is Platform Independent.

Framework used:-The Project Uses the Document Object Modelling framework to
		read the data from file and displaying it in Tree Structure.

Features:-	The Application let you browse files which you want to open
		in treeview. Also it let you select multiple root items with
		checkboxes and will be highlighting selected items with Blue.

Code Structure:-There are mainly 2 Classes which is DomItem and DomModel.
		DomItem is reading item nodes of Document, while DomModel
		is used for modelling the Document in tree structure.

Development:-	QT Creator 6.2 LTS
Environment
********************************************************************************

Guide to Use:

1. Launch the exe application for windows or Executable File in Linux.
2. A window will appear with a Menubar containing File button.
3. Click File --> Open.
4. Locate and Select XML file and open it.
5. The XML content will be now available in the TreeView of application 
   containing Checkboxes at the Root.

********************************************************************************