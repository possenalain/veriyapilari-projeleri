package Prolab4;

import java.util.ArrayList;

public class Kategori {

	private String kategoriIsmi;
	private String kategoriYolu;
	private int altKategoriSayisi;
	private int kullaniciSayisi;
	private int rezervasyonSayisi;
	private int derinlik;
	
	private Kategori Ustkategori;
    
	
	ArrayList<Kategori> altKategoriler;
	KullaniciHeap<Kullanici> kullaniciAgaci;
	public Kategori(){
		
		this.altKategoriler=new ArrayList<Kategori>();
		this.altKategoriSayisi=0;
		
		this.kullaniciSayisi=0;
		this.derinlik=0;
		
		kullaniciAgaci=new KullaniciHeap<Kullanici>();
		kullaniciAgaci.baba=this;
	}


	public void bilgi() {
		System.out.println("----------------------------------------------");
		System.out.println("Isim:"+this.getKategoriIsmi());
		System.out.println("Yolu:"+this.getKategoriYolu());
		System.out.println("Alt k sayisi:"+this.getAltKategoriSayisi());
		System.out.println("toplam Kullanici:"+this.getKullaniciSayisi());
		System.out.println("direkt Kullanici:"+this.kullaniciAgaci.kullanicilar.size());
		System.out.println("Rezervasyon sayisi:"+this.getRezervasyonSayisi());
		System.out.println("Derinlik:"+this.getDerinlik());

	}
	
	

	public String getKategoriIsmi() { return kategoriIsmi; } 
	public void setKategoriIsmi(String kategoriIsmi) { this.kategoriIsmi = kategoriIsmi; }

	public String getKategoriYolu() { return kategoriYolu; } 
	public void setKategoriYolu(String kategoriYolu) { this.kategoriYolu = kategoriYolu; }

	public int getAltKategoriSayisi() { return altKategoriSayisi; }
	public void setAltKategoriSayisi(int altKategoriSayisi) { this.altKategoriSayisi =  altKategoriSayisi; } 

	public int getDerinlik() { return derinlik; }
	public void setDerinlik(int derinlik) { this.derinlik =  derinlik; }

	public int getKullaniciSayisi() { return kullaniciSayisi; } 
	
	public int getRezervasyonSayisi() { return rezervasyonSayisi; } 
	public void setRezervasyonSayisi(int rezervasyonSayisi) { this.rezervasyonSayisi = rezervasyonSayisi; }

	
	

  public Kullanici AddKullanici(Kullanici K) {

	  if(K!=null) {
		  K=kullaniciAgaci.InsertKullanici(K);
	  }
	  
	  
	  return K;
  }
  
  
  public void KullaniciSayisiArtir() {

	  this.kullaniciSayisi++;
	  
	  if(this.Ustkategori!=null)
	  this.Ustkategori.KullaniciSayisiArtir();
  }

  
  public void KullaniciSayisiAzalt() {

		 this.kullaniciSayisi--;
		  if(this.Ustkategori!=null) {
		  this.Ustkategori.KullaniciSayisiAzalt();
	  }
	  }

  public void RezervasyonSayisiArtir() {
      
	  this.rezervasyonSayisi++;
	  
	  if(this.Ustkategori!=null)
	  this.Ustkategori.RezervasyonSayisiArtir();
  }
  
  public void RezervasyonSayisiAzalt() {

		 this.rezervasyonSayisi--;
		  if(this.Ustkategori!=null) {
		  this.Ustkategori.RezervasyonSayisiAzalt();
	  }
		  
	  }

  
  public void RemoveKullanici(String KullaniciId) {
	  
	  kullaniciAgaci.KullaniciSilme2(KullaniciId.trim());
	  
	  
  }
 

 public void RemoveAllKullanici() {
	  kullaniciAgaci.KullaniciSilme1();
  }
  
  
 public Kategori addAltKategori(Kategori kategori) { 

		if(kategori.kategoriIsmi=="rezervasyon"&&kategori.kategoriYolu=="") {//ROOT KATEGORI NODE TANIMLA VE DONDUR
			kategori=new Kategori();
			kategori.setKategoriIsmi("rezervasyon");
			kategori.setKategoriYolu("");
			kategori.Ustkategori=null;
			System.out.println("#####ROOT eklendi");
			return kategori;
		}

		else {//ALT KATEGORI

			String eklenecekKatYolu[]=kategori.kategoriYolu.split(":");
			boolean notInAltKategori=true;

			for(int i=0;i<this.altKategoriler.size();i++) {

				if((kategori.kategoriYolu.startsWith(this.altKategoriler.get(i).kategoriYolu))){

					notInAltKategori=false;

					if((kategori.kategoriYolu.equalsIgnoreCase(this.altKategoriler.get(i).kategoriYolu)
							&&kategori.kategoriIsmi.equalsIgnoreCase(this.altKategoriler.get(i).kategoriIsmi))
							){


						//ALT KATEGORY VARDI
						//System.out.println("######KATEGORI VARDI");
						return this.altKategoriler.get(i);

					}

					else if((kategori.kategoriYolu.startsWith(this.altKategoriler.get(i).kategoriYolu))
							&&(this.altKategoriler.get(i).derinlik<eklenecekKatYolu.length)){


						//BURDAN ASAGI DOGRU DEVAM ET BUNUN ALT KATEGORI OLACAK
						// System.out.println("#####INIYORUM ASAGI");
						
						return   this.altKategoriler.get(i).addAltKategori(kategori);
					}	

				}
			}

			if(notInAltKategori) {
				//YA ALTKATEGORILER BOS YADA ICINDEN BULUNMADI YENI EKLENMESI LAZIM
				Kategori temp=this;
				for(int i=this.derinlik;i<eklenecekKatYolu.length;i++) {
					//System.out.println("#####["+eklenecekKatYolu[i]+"]Ekliyorum evet--");

					Kategori temp2=new Kategori();
					temp2.setKategoriIsmi(eklenecekKatYolu[i]);
					temp2.Ustkategori=temp;
					if(temp.kategoriYolu=="")
						temp2.setKategoriYolu(temp.kategoriYolu+eklenecekKatYolu[i]);

					else
						temp2.setKategoriYolu(temp.kategoriYolu+":"+eklenecekKatYolu[i]);


					temp2.derinlik=temp.derinlik+1;
					temp.altKategoriler.add(temp2);
					temp.altKategoriSayisi++;

					temp=temp2;
				}


				return temp;

			}
		}
		return null;

	}



}
