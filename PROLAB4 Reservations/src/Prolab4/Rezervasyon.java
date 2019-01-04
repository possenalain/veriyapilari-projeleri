package Prolab4;

public class Rezervasyon {

	private String yerId;
	private String rezervasyonZamani;
	private String enlem;
	private String boylam;
	private String sehir;
	
	Rezervasyon nextRezervasyon;

	Rezervasyon(){
		this.nextRezervasyon=null;
	}
	

	public String getYerId() {return yerId;}
	public void setYerId(String yerId) {this.yerId = yerId;}

	public String getRezervasyonZamani() {return rezervasyonZamani;}
	public void setRezervasyonZamani(String rezervasyonZamani) {this.rezervasyonZamani = rezervasyonZamani;}

	public String getEnlem() {	return enlem;}
	public void setEnlem(String enlem) {this.enlem = enlem;}

	public String getBoylam() {	return boylam;}

	public void setBoylam(String boylam) {this.boylam = boylam;}

	public String getSehir() {	return sehir;}

	public void setSehir(String sehir) {	this.sehir = sehir;}

	public Rezervasyon getNextRezervasyon() {	return nextRezervasyon;}

	public void setNextRezervasyon(Rezervasyon nextRezervasyon) {this.nextRezervasyon = nextRezervasyon;}


}
