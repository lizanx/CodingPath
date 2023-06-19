def binomial_coeff(n, k):
    """计算(n, k)的二项式系数.
    n: 试验次数
    k: 成功次数
    返回：int
    """
    # if k == 0:
    #     return 1
    # if n == 0:
    #     return 0
    # res = binomial_coeff(n-1, k) + binomial_coeff(n-1, k-1)
    # return res
    return 1 if k == 0 else 0 if n == 0 else binomial_coeff(n-1, k) + binomial_coeff(n-1, k-1)


if __name__ == '__main__':
    print(binomial_coeff(5, 8))