import tkinter as tk
from tkinter import messagebox
import konversi_fungsi
import error_handling
import regula_falsi

def hitung():
    fungsi = entry_fungsi.get()
    batas_bawah = entry_bawah.get()
    batas_atas = entry_atas.get()
    toleransi = entry_error.get()
    iterasi_max = entry_iterasi.get()

    try:
        # Mengkonversi fungsi
        fungsi_terkonversi = konversi_fungsi.konversi_fungsi(fungsi)
        
        # Memeriksa error
        error_handling.periksa_error(fungsi_terkonversi, batas_bawah, batas_atas, toleransi, iterasi_max)
        
        # Melakukan perhitungan Regula Falsi
        hasil = regula_falsi.hitung_regula_falsi(fungsi_terkonversi, batas_bawah, batas_atas, toleransi, iterasi_max)
        
        # Menampilkan hasil
        output_label.config(text=hasil)
    except ValueError as e:
        messagebox.showerror("Error", str(e))

# Tkinter Setup
root = tk.Tk()
root.title("Kalkulator Regula Falsi")

tk.Label(root, text="Masukkan Fungsi:").pack()
entry_fungsi = tk.Entry(root)
entry_fungsi.pack()

tk.Label(root, text="Masukkan Batas Bawah:").pack()
entry_bawah = tk.Entry(root)
entry_bawah.pack()

tk.Label(root, text="Masukkan Batas Atas:").pack()
entry_atas = tk.Entry(root)
entry_atas.pack()

tk.Label(root, text="Masukkan Toleransi Error:").pack()
entry_error = tk.Entry(root)
entry_error.pack()

tk.Label(root, text="Masukkan Iterasi Maksimum:").pack()
entry_iterasi = tk.Entry(root)
entry_iterasi.pack()

btn_hitung = tk.Button(root, text="Hitung", command=regula_falsi)
btn_hitung.pack()

output_label = tk.Label(root, text="")
output_label.pack()

root.mainloop()
