# Hack Assembler (Nand2Tetris - Project 6)
Bu proje, Nand2Tetris kursunun/kitabının 6. projesi kapsamında geliştirilmiş, Hack Assembly dilinde yazılmış kaynak kodlarını (.asm) donanım simülatörünün çalıştırabileceği saf 1 ve 0'lardan oluşan makine diline (.hack) çeviren masaüstü konsol aracıdır.

# 🚀 Projenin Amacı

* Bilgisayar mimarisinin en alt katmanı ile yüksek seviyeli yazılım dünyası arasındaki köprüyü kurmak amacıyla tasarlanmıştır. Bu araç sayesinde, insan okunabilir assembly komutları (semboller, etiketler ve değişkenler dahil) işlemcinin doğrudan yürütebileceği binary komut setine dönüştürülür.

# 🛠️ Kullanılan Teknolojiler ve Araçlar

Programlama Dili: C# (.NET)

* Veri Yapıları: Dictionary (Symbol Table yönetimi için)

* Mimari: İki geçişli (Two-pass) derleme mantığı (Önce etiketlerin okunması, sonra kod çevirisi).

# ⚙️ Nasıl Çalışır? (Mimarinin İşleyişi)

Assembler, kaynak .asm dosyasını işlerken sırasıyla şu aşamalardan geçer:

Preprocessor & Parser (Ayrıştırma): Dosyadaki boşlukları ve yorum satırlarını (//) temizler. Her satırı okuyarak komutun tipini ayırt eder:

A-Instruction (@value): Sabit bir sayıya veya değişkene işaret eden komutlar.

C-Instruction (dest=comp;jump): ALU operasyonlarını ve veri transferlerini yöneten komutlar.

L-Instruction ((LABEL)): Kod içi atlama noktalarını belirten etiketler.

Symbol Table (Sembol Tablosu):

Varsayılan olarak Hack mimarisinin ön tanımlı register isimlerini (R0-R15, SCREEN, KBD vb.) başlangıç adresleriyle tabloya yükler.

Birinci geçişte tüm etiketleri (LABEL) bulup ROM adresleriyle birlikte hafızaya kaydeder.

İkinci geçişte değişkenleri (@sayac) RAM'in serbest başlangıç adresi olan 16'dan itibaren dinamik olarak adresler.

Code Generation (Kod Üretimi): Ayrıştırılan her parça (dest, comp, jump ve A-komutlarının binary karşılıkları) 16-bitlik string dizilerine çevrilerek .hack uzantılı çıktı dosyasına yazılır.

```text
📂 Proje Yapısı
Plaintext
HackAssembler/
│
├── Program.cs          # Giriş noktası ve dosya okuma/yazma akışı
├── Parser.cs           # Dosyayı satır satır okuyup komutları ayıran sınıf
├── Code.cs             # Dest, Comp ve Jump alanlarını binary koda çeviren sınıf
├── SymbolTable.cs      # Değişkenleri ve etiketleri yöneten bellek tablosu
└── README.md           # Proje dokümantasyonu
