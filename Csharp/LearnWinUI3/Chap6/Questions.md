1. When will Windows put a WinUI 3 app into a suspended state?
> WinUI 3 app won't enter suspend state, unlike UWP.

2. When should you save the app state to ensure it is not lost if an application is closed?
> When the last `Window`(usually `MainWindow`) is closed, save state in its `Closed` function.

3. What is the event you can handle on a Page class to perform some logic when every element on a page has finished loading?
> `Loaded`

4. What is a Micro ORM?
> A light-weight Object-Relational-Mapper. 

5.What is the name of the Dapper package that adds CRUD helpers such as Delete and DeleteAsync?
> Dapper.Contrib

6. What is one of the powerful features of some more full-featured ORMs, such as Entity Framework?
> NHibernate / DevExpress XPO

7. What is the name of a tool that can be used to inspect data in a SQLite database?
> DB Browser for Sqlite.
