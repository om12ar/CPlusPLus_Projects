
Students Management System   

The file structure is length-indicator based filed, length-indicator based record.  

· Add new record, check first the avail list if you can use a deleted slot or not. Use the worst fit strategy. If the remaining space is greater than 5 bytes, place them back to avail list.  
· Update a record given the ID, if the new record is bigger than the old one just delete the old record and make new insert for the new one. If the new record  
less than the old one, then place the remaining spaces back to avail list only if these spaces greater than 5 bytes.  
· Delete a record, update the Avail List after each delete. Keep the avail list sorted descending.
· Search for a record given an ID, if found print its data.  
· Compact Avail List: if there are two or more physically adjacent deleted records  
in avail list combine them into a larger one.  