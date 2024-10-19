def periksa_error(fungsi, batas_bawah, batas_atas, toleransi, iterasi):
    try:
        float(batas_bawah)
        float(batas_atas)
        float(toleransi)
        int(iterasi)
    except ValueError:
        raise ValueError("Input batas, toleransi, atau iterasi tidak valid.")
    
    if batas_bawah >= batas_atas:
        raise ValueError("Batas bawah harus lebih kecil dari batas atas.")
    
    # Tambah validasi lainnya sesuai kebutuhan
