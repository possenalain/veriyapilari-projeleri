package Prolab4;

public class Kullanici{

	String kullaniciId;
	String kategoriIsimi;
	int rezervasyonSayisi;
	
	RezervasyonListi RzListi;
	
	Kategori Babam;
	
	Kullanici(){
		this.RzListi=new RezervasyonListi();
		this.rezervasyonSayisi=0;
		this.Babam=null;
	}
	
	public String getKullaniciId() {return kullaniciId;}
	public void setKullaniciId(String kullaniciId) {this.kullaniciId = kullaniciId;}

	public String getKategoriIsimi() {return kategoriIsimi;}
    public void setKategoriIsimi(String kategoriIsimi) {this.kategoriIsimi = kategoriIsimi;}

	public int getRezervasyonSayisi() {return rezervasyonSayisi;}
	public void setRezervasyonSayisi(int rezervasyonSayisi) {this.rezervasyonSayisi = rezervasyonSayisi;}

	public Kategori getBaba() {return this.Babam;}
	public void setBaba(Kategori Baba) {this.Babam = Baba;}
	
	public boolean CompareKullanici(Kullanici lower) {
		
		if(this.rezervasyonSayisi>lower.rezervasyonSayisi) {
			return true;
		}
		return false;
	}
	
	public void addRezervasyon(String[] splitted) {
		this.RzListi.RezervasyonOlustur(splitted);
		this.setRezervasyonSayisi(this.getRezervasyonSayisi()+1);
		Kategori babasi=this.getBaba();
		babasi.kullaniciAgaci.HeapifyUp(babasi.kullaniciAgaci.kullanicilar.indexOf(this));
		babasi.RezervasyonSayisiArtir();
		}
	
	
	public void KullaniciBilgi() {
		
				//REZERVASYONUN BILGILERI YAZDIR 
		System.out.println("Kullanici: "+this.getKullaniciId());
		System.out.println("Kategori: "+this.getKategoriIsimi());
		System.out.println("Rezervasyon sayisi : "+this.getRezervasyonSayisi());
				
			
		}
	
	
}
