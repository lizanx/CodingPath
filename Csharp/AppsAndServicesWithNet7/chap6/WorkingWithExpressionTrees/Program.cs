using System.Linq.Expressions;

ConstantExpression one = Expression.Constant(1, typeof(int));
ConstantExpression two = Expression.Constant(2, typeof(int));
BinaryExpression add = Expression.Add(one, two);

Expression<Func<int>> exprTree = Expression.Lambda<Func<int>>(add);

Func<int> compiledTree = exprTree.Compile();

WriteLine($"Result: {compiledTree()}");