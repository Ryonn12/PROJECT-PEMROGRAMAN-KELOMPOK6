def regula_falsi_calculation(f, a, b, tolerance, max_iter):
    """
    Mengimplementasikan metode Regula Falsi untuk mencari akar fungsi f.

    Args:
        f (function): Fungsi yang akan dicari akarnya.
        a (float): Batas bawah.
        b (float): Batas atas.
        tolerance (float): Toleransi kesalahan yang diizinkan.
        max_iter (int): Jumlah iterasi maksimum.

    Returns:
        list: Daftar hasil per iterasi (iterasi, a, b, x, f(x), error).
    """
    results = []
    for i in range(1, max_iter + 1):
        fa = f(a)
        fb = f(b)
        x = a - (fa * (b - a)) / (fb - fa)
        fx = f(x)
        error = abs(fx)

        results.append((i, a, b, x, fx, error))

        if error < tolerance:
            break

        if fa * fx < 0:
            b = x
        else:
            a = x

    return results
