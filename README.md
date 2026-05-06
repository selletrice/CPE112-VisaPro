# VisaPro : International Student Visa + 90 Days Deadline & Document Support System

VisaPro is a specialized management system designed to assist international students at KMUTT with the complex process of visa extensions and 90-day reporting. By combining structured roadmaps with interactive document checklist, the system ensures students stay compliant with immigration regulations.

## Overview
For international students, administravtice processes like visa support letters can be overwhelming. **VisaPro** simplifies these requirements into a manageable digital experience by employing advanced C programming data structures like **Hash Tables, Linked Lists, Binary Trees and Priority Queue**.

## Features
* **Centralized Roadmap:** Guides students through the four key steps of **Registration, Document Collection, Immigration Visit and Visa Issued**.
* **Interactive Document Logic:**   
       - Features Binary Tree structure for detailed checklist based on official KMUTT Visa System.
       - Uses post-order transversal to ensure that all sub-requirements (children) are met before a major category (parent) can be marked complete.
* **Deadline Management:** 
       - Calculates the days left until the visa and 90-day report expire based on user input.
       - Utilize Priority Queue to display an urgent list of students sorted by the least number of days left.
* **Automated Progress Tracking:** Tracks records collection progress (1 for Yes and 0 for No) and gives feedback on remaining files to collect.
* **Renewal Support:** Lets users restart the process with new expiry dates and resets all document trees to uncollected automatically.

## File Structure 
- ```├── main.c:``` Central control flow and menu system.
- ```├── student_db.c:``` Handles student registration and O(1) searching using a Hash Table.
- ```├── process_manager.c:``` Manages the stage-based roadmap via a Linked List.
- ```├── document_logic.c:``` Implements the Binary Tree document checklists and Post-order logic.
- ```├── deadline_manager.c:``` Manages expiry dates, Priority Queue sorting, and urgent student lists.
- ```├── visa_pro.h:``` Global header containing structures for student, docNode, and stageNode.
- ```├── Makefile```
- ```└── README.md```

## How to Use
1. **Register:** Type in your Name and Student ID to build your profile and document trees.
2. **Set Due Dates:** Enter the expiry dates of your current Visa and 90 day report.
3. **Check Status:** See where you are in the queue based on how urgent your deadline is.
4. **Complete Checklist:** Interact with the Document Logic module to verify your files.
If incomplete, the system will specify which documents are missing.
If complete, the system will prompt you to move to the Immigration Office.
5. **Renew:** Once you visa is extended, update your expiry date to restart the tracking cycle.

## Credits & Collaboration
This project was developed by a team of first-year Computer Engineering students at KMUTT.
**Role Division:**
* **Architect**(Koshen Lille Del Mundo Escanlar - 3493): Responsible for the Hash Table database, Linked List roadmap, and main framework.
* **Logic Lead**(Leonora Shrestha - 3404): Responsible for Document Tree architecture, Post-order Traversal logic and report.
* **Deadline Specialist**(Phung Ngoc Minh Anh Le - 3462): Responsible for the Priority Queue implementation, date calculation logic and memory management.

We consistently keep regular meetings. This helps us a lot in communicating with our team and in debugging. This project helped us with not just courses but to learn about importance of TEAMWORK.

## Acknowledgement
* **Professors: Dr. Aye Hninn Khine, Assoc. Prof. Dr. Natasha Dejdumrong & Mr. Naveed Sultan:** We would like to thank all of the professors for the opportunity to apply Data Structures and Algorithms to a real-world student administrative challenge.
* **KMUTT International Affairs Office:** For the official documentation and checklists that formed the logic of this system.
